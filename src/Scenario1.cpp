#include "Scenario1.hpp"

void Scenario1::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario1.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-1 file ! \n";

    std::string name;
    int numberOfBirds;
    int index = 0; // index to track position in birds vector

    while (input >> numberOfBirds >> name)
    {
        for (int i = 0; i < homes.size(); i++)
        {
            // convert the City pointer to a Home pointer
            auto home = std::dynamic_pointer_cast<Home>(homes[i]);

            for (int j = 0; j < numberOfBirds; j++)
            {
                Bird temp = readBird(name, birds); // create a new bird of this type
                home->push(temp); // add the bird to the current home
                birds[index].setHomePlace(homes[i]->getCityName()); // set the home city name for this bird
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

    // create a map for homes using city names as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    // create a map for enemies using city name as key for quick access
    std::unordered_map<std::string, std::shared_ptr<City>> enemyMap;
    for (auto &enemy : enemies)
        enemyMap[enemy->getCityName()] = enemy;

    for (auto &bird : birds)
    {
        auto itHome = homeMap.find(bird.getHomePlace()); // find the bird's home
        if (itHome == homeMap.end())
            continue;

        ld distance = 0;
        std::vector<std::shared_ptr<City>> path;
        
        // find the best target for the bird using findBestPairFor
        auto [enemy, canDestroy] = control.findBestPairFor(itHome->second, bird, path, distance);

        std::cout << "Bird : " << bird.getName() << "\nPath: ";
        if (canDestroy != 1)
            control.deadBird(bird, distance); // handle birds that cannot reach their target
        else
        {
            control.setReachBird(enemy, bird, path); // register bird's path and target
            for (auto &city : path)
            {
                std::cout << city->getCityName() << " ";
            }
        }
        std::cout << "\n---------------------------------------\n\n";
    }

    std::cout << "\n---------------------------------------\n";

    control.attack(); // execute attacks on enemy cities

    auto aliveBirds = control.getBirds(); // get surviving birds after attack
    for (auto &bird : aliveBirds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "---------------------------------------\n";
    std::cout << "Total Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
