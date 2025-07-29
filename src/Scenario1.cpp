#include "Scenario1.hpp"

void Scenario1::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
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
            for (int i = 0; i < count; i++)
            {
                Bird temp = readBird(name, birds);
                homes[i].push(temp);
            } 
        }
    }
    input.close();
}
void Scenario1::printOutput(Controler &control , std::vector<std::shared_ptr<City>> &homes)
{
    ld totalDamage = 0.0;

    for ( auto & home : homes )
    {
        auto myHome = std::dynamic_pointer_cast<Home>(home);
        for ( auto & bird : myHome->getMyBirds())
        {
            std::string enemy = control.findBestPairFor(home , bird);
            auto path = control.aStar(home->getCityName() , enemy , bird);
            totalDamage += control.totoalDamage(path, bird);

            std::cout << "-----------------------------\n";
            std::cout << "\nBird : " << bird.getName() << "\nPath: ";     
            for (auto & city : path)
            {
                std::cout << city->getCityName() << " ";
            }
            std::cout << "\nTotal Damage: " << totalDamage << "\n";
        }
    }
}
