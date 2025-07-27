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
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            readBird(name, birds);
        }
    }

    input.close();
}
void Scenario1::printOutput(Controler &control)
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
