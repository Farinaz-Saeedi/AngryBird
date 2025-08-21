#include "Scenario2.hpp"

void Scenario2::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario2.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-2 file ! \n";

    ll numberOfBirds;
    std::string birdName, cityName;

    while (input >> numberOfBirds)
    {
        for (int i = 0; i < numberOfBirds; i++)
        {
            input >> birdName >> cityName;

            Bird temp = readBird(birdName, birds); // create a new bird of this type
            birds.back().setHomePlace(cityName); // set the bird's home city

            // find the home city object and add the bird to it
            auto itHome = std::find_if(homes.begin(), homes.end(), [&](auto &home)
            {
                auto h = std::dynamic_pointer_cast<Home>(home);
                return h && h->getCityName() == cityName; 
            });

            if (itHome != homes.end())
            {
                std::dynamic_pointer_cast<Home>(*itHome)->push(temp); // add bird to home's list
            }
        }
    }

    input.close();
}
void Scenario2::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ld totalDamage = 0.0;
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();

    // create a map from home city names to their objects for quick lookup
    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    // create a map from enemy city names to their objects for quick lookup
    std::unordered_map<std::string, std::shared_ptr<City>> enemyMap;
    for (auto &enemy : enemies)
        enemyMap[enemy->getCityName()] = enemy;

    // iterate through each bird to determine its path and actions
    for (auto &bird : birds)
    {
        auto itHome = homeMap.find(bird.getHomePlace());
        if (itHome == homeMap.end())
            continue;

        ld distance = 0;
        std::vector<std::shared_ptr<City>> path;
        auto [enemy, canDestroy] = control.findBestPairFor(itHome->second, bird, path, distance); // find best target city

        std::cout << "Bird : " << bird.getName() << "\nPath: ";

        if (canDestroy != 1) // bird cannot reach target
            control.deadBird(bird, distance);
        else
        {
            control.setReachBird(enemy, bird, path);
            for (auto &city : path)
            {
                std::cout << city->getCityName() << " ";
            }
        }
        std::cout << "\n---------------------------------------\n\n";
    }

    std::cout << "\n---------------------------------------\n";

    control.attack(); // execute attacks by enemies

    auto aliveBirds = control.getBirds();
    for (auto &bird : aliveBirds) // sum total damage caused by surviving birds
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "---------------------------------------\n";
    std::cout << "Total Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
