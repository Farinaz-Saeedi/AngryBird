#include "Scenario4.hpp"

void Scenario4::readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes)
{
    std::ifstream input("../src/Scenario4.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-4 file ! \n";

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
void Scenario4::printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes)
{
    ld totalDamage = 0.0;

    for (auto &bird : control.getBirds())
    {
        auto path = control.aStar(control.getTopBestPair().first, control.getTopBestPair().second, bird);

        std::cout << "\nBird : " << bird.getName() << "\nPath: ";
        for (auto &city : path)
        {
            std::cout << city << " ";
        }

        std::cout << "\n\n";
        totalDamage += control.totoalDamage(path, bird);
    }

    std::cout << "Total Damage: " << totalDamage << "\n";
}