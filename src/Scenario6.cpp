#include "Scenario6.hpp"

void Scenario6::readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes)
{
    std::ifstream input("../src/Scenario6.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-6 file ! \n";

    ll count;
    std::string name;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            Bird temp = readBird(name, birds);

            input >> name;
            birds[birds.size() - 1].setHomePlace(name);

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (home->getCityName() == name)
                {
                    home->push(temp);
                    break;
                }
            }
        }
    }

    input.close();
}
void Scenario6::printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) 
{
    ll totalDamage = 0;
    birds = control.getBirds();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();
    giveBirdsID();

    // create a map for homes using city names as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;  
            
    bool nightPass = true; // to manage the nights
    int night = 1 ; // number of night
    while(!birds.empty())
    {
        std::cout << "Night " << night << " begins ...\n\n";

        firstOptions.clear();
        firstOptions.reserve(birds.size());

        // create a map for options using enemy name as key for quick access        
        std::unordered_map<std::string, std::vector<OptionScen6>> enemyToSecondOptions;
        
        for (auto & bird : birds)
        {
            auto itHome = homeMap.find(bird.getHomePlace());
            if (itHome == homeMap.end())
            continue;
            auto myHome = std::dynamic_pointer_cast<Home>(itHome->second);
            if (!myHome)
            continue;

            ld distance = 0.0;
            ld cost;
            std::vector<std::shared_ptr<City>> path;

            for (auto & target : control.getEnemies())
            {
                bool can = control.aStar(itHome->second->getCityName(), target->getCityName(), bird, path, distance, cost);
                if (path.empty() || !can) // check that if bird can reach the goal
                    continue;

                OptionScen6 opt{bird.getID(), itHome->second, target, path, bird.getDemolition()};
                bird.setThePath(path);
                if (control.isDetected(bird))
                {
                    // if the bird can be shot down by the enemy
                    enemyToSecondOptions[target->getCityName()].push_back(opt);
                    continue;
                } else
                {
                    firstOptions.push_back(opt); // the options which are generated 
                }
            }
        }

        // sort options based on the demolition
        std::sort(firstOptions.begin() , firstOptions.end() , [](OptionScen6 & a , OptionScen6 & b)
        {
            return a.damage < b.damage ;
        });

        std::unordered_set<int> usedBirds;  // to not use a bird twice
        usedBirds.clear();
        birdsToRemove.clear();

        if (!firstOptions.empty())
        {
            auto opt = firstOptions.back();
            int idx = getBirdIndex(opt.birdId);
            if (usedBirds.count(idx)) continue;

            control.setReachBird(opt.target->getCityName(), birds[idx], opt.path);
            std::cout << "Bird " << birds[idx].getName() <<  " | " << opt.home->getCityName() << " -> " << opt.target->getCityName();
            std::cout << "\nPath: ";
            for (auto & city : opt.path)
                std::cout << city->getCityName() << " ";
            std::cout << "\n\n";
            usedBirds.insert(idx);
            birdsToRemove.push_back(idx);
        } 
        else 
        {
            std::shared_ptr<Enemy> weakEnemy = control.getWeakEnemy();
            int capacity = weakEnemy->getDefenseLevel();
            auto opts = enemyToSecondOptions[weakEnemy->getCityName()];

            // sort options based on the demolition
            std::sort(opts.begin() , opts.end() , [](auto &a , auto &b) 
            {
                return a.damage > b.damage;
            });

            for (int i = 0 ; i < capacity + 1 ; ++i)
            {
                if ((opts.size()) < capacity + 1) // when the birds are not enough
                {
                    nightPass = false;
                    birds.clear();
                    break;
                }
                           
                int idx = getBirdIndex(opts[i].birdId);
                if (usedBirds.count(idx)) continue;

                control.setReachBird(opts[i].target->getCityName(), birds[idx], opts[i].path);

                std::cout << "Bird " << birds[idx].getName() << " | " << opts[i].home->getCityName()
                          << " -> " << opts[i].target->getCityName() << "\nPath: ";
                for (auto & city : opts[i].path)
                    std::cout << city->getCityName() << " ";
                    
                std::cout << "\n\n";
                usedBirds.insert(idx);
                birdsToRemove.push_back(idx);

            }  
        }
            
        control.attack(); // execute attacks based on assignments

        // Sorting bird indices in reverse order to prevent deletion errors
        std::sort(birdsToRemove.rbegin(), birdsToRemove.rend());
        for (int idx : birdsToRemove)
        {
            birds.erase(birds.begin() + idx);
        }
        
        if (nightPass) night++;   
        else
            std::cout << "No launches possible this night .";
        std::cout << "\n--------------------------------\n";
    }

    std::vector<Bird> aliveBirds = control.getBirds(); // get surviving birds after attack
    for (int i = 0 ; i < aliveBirds.size() ; ++i)
    {
        totalDamage += aliveBirds[i].getDemolition();
    }
    
    std::cout << "\n-- Total Damage: " << totalDamage << " --\n\n";
    std::cout << "[Number of attack nights] : " << night-1 << '\n';
}
void Scenario6::giveBirdsID()
{
    for (int i = 0 ; i < birds.size() ; ++i)
    {
        // set their first indices as ID
        birds[i].setID(i);
    }
}
int Scenario6::getBirdIndex(int id) 
{
    for (int i = 0 ; i < birds.size() ; ++i)
    {
        if (birds[i].getID() == id)
            return i;
    }
    return -1;
}