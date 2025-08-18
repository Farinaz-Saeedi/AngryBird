#include "Scenario1.hpp"

void Scenario1::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario1.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-1 file ! \n";

    std::string name;
    int count;
    int index = 0;

    while (!input.eof())
    {
        input >> count >> name;
        for (int i = 0; i < homes.size(); i++)
        {
            for (int j = 0; j < count; j++)
            {
                Bird temp = readBird(name, birds);
                auto home = std::dynamic_pointer_cast<Home>(homes[i]);
                home->push(temp);
                birds[index].setHomePlace(homes[i]->getCityName());
                index++;
            }
        }
    }
    input.close();
}

void Scenario1::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ld totalDamage = 0.0;
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();

    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    std::unordered_map<std::string, std::shared_ptr<City>> enemyMap;
    for (auto &enemy : enemies)
        enemyMap[enemy->getCityName()] = enemy;
    
    for (auto &bird : birds)
    {
        auto itHome = homeMap.find(bird.getHomePlace());
        if (itHome == homeMap.end())
            continue;

        ll distance = 0;
        std::vector<std::shared_ptr<City>> path;
        auto [enemy, canDestroy] = control.findBestPairFor(itHome->second, bird, path, distance);

        std::cout << "Bird : " << bird.getName() << "\nPath: ";
        if (canDestroy != 1)
            control.deadBird(bird, distance);
        else
        {
            control.setReachBird(enemy, bird, path);
            for (auto &city : path)
            {
                std::cout << city->getCityName() << " ";
            }
        }
        std::cout << "\n---------------------------------------\n";
        std::cout << "\n";
        
    }

    std::cout << "\n---------------------------------------\n";

    control.attack();

    auto aliveBirds = control.getBirds();
    for (auto &bird : aliveBirds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "---------------------------------------";
    std::cout << "\nTotal Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
