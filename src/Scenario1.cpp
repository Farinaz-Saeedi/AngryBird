#include "Scenario1.hpp"

void Scenario1::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario1.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-1 file ! \n";

    std::string name;
    int count;

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
            }
        }
    }
    input.close();
}

void Scenario1::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes, std::vector<Bird> &tempBirds)
{
    ld totalDamage = 0.0;
    for (auto &home : homes)
    {
        auto myHome = std::dynamic_pointer_cast<Home>(home);
        if (!myHome)
            continue;

        auto &birds = myHome->getMyBirds();
        if (birds.empty())
            continue;

        for (auto &bird : birds)
        {
            ll distance = 0;
            std::vector<std::shared_ptr<City>> path;
            auto [enemy, canDestroy] = control.findBestPairFor(home, bird, path, distance);

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
    }

    std::cout << "\n---------------------------------------\n";

    control.attack();

    auto birds = control.getBirds();
    for (auto &bird : birds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "---------------------------------------";
    std::cout << "\nTotal Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
