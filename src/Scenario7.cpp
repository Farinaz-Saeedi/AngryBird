#include "Scenario7.hpp"

int Scenario7::getNumberOfNights()
{
    return numberOfNights;
}
void Scenario7::setNumberOfNights(int numberOfNights)
{
    this->numberOfNights = numberOfNights;
}
void Scenario7::setDamage(ld damage)
{
    this->damage = damage;
}
ld Scenario7::getDamage()
{
    return damage;
}
void Scenario7::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario7.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-7 file ! \n";

    int nights;
    ll count;
    ld temp;
    std::string name;

    while (!input.eof())
    {
        input >> nights >> temp;
        setNumberOfNights(nights);
        setDamage(temp);

        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> temp;
            Bird tempBird = readBird(name, birds);

            lst.push_back({name, temp}); // Store cost

            input >> name;
            birds[birds.size() - 1].setHomePlace(name); // set the slingshot of bird 

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (home->getCityName() == name)
                {
                    home->push(tempBird); // Push bird to the corresponding home
                    break;
                }
            }
        }
    }

    input.close();
}
void Scenario7::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ld totalDamage = 0;
    ll totalCost = 0;
    int nights = getNumberOfNights();

    birds = control.getBirds();
    giveBirdsID();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();

    // create a map for homes using city names as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    // create a map for enemies using city name as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> enemyMap;
    for (auto &enemy : enemies)
        enemyMap[enemy->getCityName()] = enemy;

    for (int night = 1; night <= nights; ++night)
    {
        std::cout << "\nNight " << night << " begins...\n\n";
        options.clear();

        // Generate all attack options for this night
        for (auto & bird : birds)
        {
            auto it = homeMap.find(bird.getHomePlace());
            if (it == homeMap.end())
                continue;
            auto myHome = std::dynamic_pointer_cast<Home>(it->second);
            if (!myHome)
                continue;

            std::vector<std::shared_ptr<City>> path;
            ld distance = 0.0;
            ld cost = getBirdCost(bird.getName());
            ld pathCost;

            std::pair<std::string, bool> pair = control.findBestPairFor(it->second, bird, path, distance);
            if (!pair.second || path.empty())
                continue;

            bird.setThePath(path); 
            if (!control.isDetected(bird))
            options.push_back(OptionScen7{bird.getID(), it->second, enemyMap[pair.first], path, bird.getDemolition(), cost, bird.getDegree(), false});   
            else
            secondOptions.push_back(OptionScen7{bird.getID(), it->second, enemyMap[pair.first], path, bird.getDemolition(), cost, bird.getDegree(), true});
        }

        if (options.empty())
        {
            options = secondOptions;
        } 
        if (secondOptions.empty() && options.empty())
        {
            std::cout << "No launches possible this night .\n";
            continue;
        }

         // Select birds using knapsack approach (maximize damage / minimize cost)
         ld nightDamage = 0;
        auto chosen = knapsackMinCost(options, damage, nightDamage);

        ll nightCost = 0;
        std::vector<int> birdsToRemove;

        // Execute chosen attacks
        for (auto & opt : chosen)
        {
            int idx = getBirdIndex(opt.birdId);
            if (idx == -1)
                continue;

            control.setReachBird(opt.target->getCityName(), birds[idx], opt.path);

            std::cout << "Bird " << birds[idx].getName()
                      << " | " << opt.home->getCityName()
                      << " -> " << opt.target->getCityName()
                      << " | Cost: " << opt.cost
                      << " | Damage: " << opt.damage
                      << "\nPath: ";
            for (auto &city : opt.path)
                std::cout << city->getCityName() << " ";
            std::cout << "\n--------------------------------\n";

            // nightDamage += opt.damage;

            nightCost += opt.cost;
            birdsToRemove.push_back(idx);
        }

        totalDamage += nightDamage;

        totalCost += nightCost;

        std::cout << "Night damage: " << nightDamage
                  << " | Night cost: " << nightCost
                  << " | Total damage so far: " << totalDamage << "\n";

        if (totalDamage >= getDamage())
        {
            std::cout << "\n Enemy surrendered :)";
            break;
        }

        // Sorting bird indices in reverse order to prevent deletion errors
        std::sort(birdsToRemove.rbegin(), birdsToRemove.rend());
        for (int idx : birdsToRemove)
            birds.erase(birds.begin() + idx);

        control.attack(); // execute attacks based on assignments
    }

    std::cout << "\n--- Total Damage: " << totalDamage << " | Total Cost: " << totalCost << " ---\n";
}

std::vector<OptionScen7> Scenario7::knapsackMinCost(const std::vector<OptionScen7> &options, ld targetDamage, ld & nightDamage)
{
    int n = options.size();

    std::vector<OptionScen7> chosen;
    ld currentDamage = 0;
    int birdsUsed = 0;
    int numberOfKills = 0;

    // Sort by damage-to-cost ratio descending
    std::vector<OptionScen7> sorted = options;
    std::sort(sorted.begin(), sorted.end(), [](const OptionScen7 &a, const OptionScen7 &b)
              { return (a.damage / a.cost) > (b.damage / b.cost); });

    for (auto & opt : sorted)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(opt.target);
        int lvl = enemy->getDefenseLevel();
        if (currentDamage >= targetDamage)
            break;

        chosen.push_back(opt);
        if (!opt.isDetect)
        {
            std::cout << "plus\n";
            currentDamage += opt.damage;
        }
        else 
        {
            std::cout << "second\n";
            if (numberOfKills >= lvl)
                currentDamage += opt.damage;
            std::cout << numberOfKills << " = num \n";
            numberOfKills++;
        }
        birdsUsed++;
    }
    nightDamage = currentDamage;

    return chosen;
}
ld Scenario7::getBirdCost(const std::string &birdName)
{
    auto it = std::find_if(lst.begin(), lst.end(), [&birdName](const std::pair<std::string, ld> &entry)
    { return entry.first == birdName; });

    if (it != lst.end())
    {
        return it->second;
    }

    return 0.0;
}
void Scenario7::giveBirdsID()
{
    for (int i = 0; i < birds.size(); ++i)
    {
        birds[i].setID(i);
    }
}
int Scenario7::getBirdIndex(int id)
{
    for (int i = 0; i < birds.size(); ++i)
    {
        if (birds[i].getID() == id)
            return i;
    }
    return -1;
}