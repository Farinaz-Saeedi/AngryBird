#include "Scenario2.hpp"

void Scenario2::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario2.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-2 file ! \n";

    ll count;
    std::string name, city;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            Bird temp = readBird(name, birds);

            input >> city;
            birds[birds.size() - 1].setHomePlace(city);

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (!home)
                    continue;

                if (home->getCityName() == city)
                {
                    home->push(temp);
                    break;
                }
            }
        }
    }

    input.close();
}
void Scenario2::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
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
    for (auto & bird : birds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "---------------------------------------";
    std::cout << "\nTotal Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
