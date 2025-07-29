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
void Scenario6::printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) {}