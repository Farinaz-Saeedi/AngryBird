#include "Scenario5.hpp"

int Scenario5::getNumberOfNights()
{
    return numberOfNights;
}
void Scenario5::setNumberOfNights(int numberOfNights)
{
    this->numberOfNights = numberOfNights;
}
void Scenario5::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario5.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-5 file ! \n";

    int nights;
    ll count;
    std::string name;

    while (!input.eof())
    {
        input >> nights;
        setNumberOfNights(nights);

        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            Bird temp = readBird(name, birds);

            input >> name;
            birds[birds.size() - 1].setHomePlace(name); // set the slingshot of bird 

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (home->getCityName() == name)
                {
                    home->push(temp); // push bird to a vector for each home
                    break;
                }
            }
        }
    }
    input.close();
}
void Scenario5::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ll totalDamage = 0;
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();

    // create a map for homes using city names as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> homeMap; 
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    bool nightPass = true;
    for (int night = 1; night <= getNumberOfNights(); ++night)
    {
        std::cout << "\nNight " << night << " begins ...\n\n";

        control.newSpies(night); // read new spies of each night from file 

        firstOptions.clear();
        allOptions.clear();
        firstOptions.reserve(birds.size());

        // create a map for options using enemy name as key for quick access   
        std::unordered_map<std::string, std::vector<OptionScen5>> enemyToSecondOptions;

        for (int b = 0; b < birds.size(); ++b)
        {

            auto itHome = homeMap.find(birds[b].getHomePlace());
            if (itHome == homeMap.end())
                continue;
            auto myHome = std::dynamic_pointer_cast<Home>(itHome->second);
            if (!myHome)
                continue;

            ld distance = 0.0;
            ld cost;
            std::vector<std::shared_ptr<City>> path;

            for (auto &target : control.getEnemies())
            {
                bool can = control.aStar(itHome->second->getCityName(), target->getCityName(), birds[b], path, distance, cost);
                if (path.empty() || !can) // check that if bird can reach the goal
                    continue;
                
                OptionScen5 opt{b, birds[b].getDegree(), itHome->second, target, path, birds[b].getDemolition()};
                birds[b].setThePath(path); 
                allOptions.push_back(opt); // push all possible options
                if (control.isDetected(birds[b]))
                {
                    // if the bird can be shot down by the enemy
                    enemyToSecondOptions[target->getCityName()].push_back(opt);
                    continue;
                } else
                    firstOptions.push_back(opt);
            }
        }

        // sort first options based on number of spies and damage
        std::sort(firstOptions.begin() , firstOptions.end() , [](OptionScen5 & a , OptionScen5 & b)
        {
            if ( a.spyNum != b.spyNum ) return a.spyNum > b.spyNum ;
            return a.damage < b.damage ;
        });

        std::unordered_set<int> usedBirds; // to not use a bird twice
        usedBirds.clear();
        birdsToRemove.clear();

        if (!firstOptions.empty())
        {
            auto opt = firstOptions.back();

            control.setReachBird(opt.target->getCityName(), birds[opt.birdIdx], opt.path);
            std::cout << "Bird " << birds[opt.birdIdx].getName() <<  " | " << opt.home->getCityName() << " -> " << opt.target->getCityName();
            std::cout << "\nPath: ";
            for (auto & city : opt.path)
                std::cout << city->getCityName() << " ";
            std::cout << "\n--------------------------------\n";
            birdsToRemove.push_back(opt.birdIdx);
        } 
        else // when the first options vector is empty
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
                if (usedBirds.count(opts[i].birdIdx)) continue;
                if ((opts.size()) < capacity + 1)
                {
                    nightPass = false; // to manage the night 
                    birds.clear();
                    break;
                }

                control.setReachBird(opts[i].target->getCityName(), birds[opts[i].birdIdx], opts[i].path);

                std::cout << "Bird " << birds[opts[i].birdIdx].getName() << " | " << opts[i].home->getCityName()
                          << " -> " << opts[i].target->getCityName() << "\nPath: ";
                for (auto & city : opts[i].path)
                    std::cout << city->getCityName() << " ";
                std::cout << "\n--------------------------------\n";

                usedBirds.insert(opts[i].birdIdx);
                birdsToRemove.push_back(opts[i].birdIdx);
            }
        }
        
        if (night == getNumberOfNights()) // for the last night 
        {
            for (auto & opt : allOptions) // use all options to increase destruction
            {
                if (usedBirds.count(opt.birdIdx)) continue;
                
                control.setReachBird(opt.target->getCityName(), birds[opt.birdIdx], opt.path);
                
                std::cout << "Bird " << birds[opt.birdIdx].getName() << " | " << opt.home->getCityName()
                << " -> " << opt.target->getCityName() << "\nPath: ";
                for (auto & city : opt.path)
                std::cout << city->getCityName() << " ";
                std::cout << "\n--------------------------------\n";
                usedBirds.insert(opt.birdIdx);
                birdsToRemove.push_back(opt.birdIdx);
            }
        }

        if (!nightPass) std::cout << "No launches possible this night .\n";

        control.attack(); // execute attacks based on assignments

        // Sorting bird indices in reverse order to prevent deletion errors
        std::sort(birdsToRemove.rbegin(), birdsToRemove.rend());
        for (int idx : birdsToRemove)
        {
            birds.erase(birds.begin() + idx);
        }
    }

    auto aliveBirds = control.getBirds(); // get surviving birds after attack
    for (int i = 0 ; i < aliveBirds.size() ; ++i)
    {
        totalDamage += aliveBirds[i].getDemolition();
    }
    
    std::cout << "\n-- Total Damage: " << totalDamage << " --\n";
}