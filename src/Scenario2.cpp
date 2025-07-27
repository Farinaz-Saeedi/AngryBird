#include "Scenario2.hpp"

void Scenario2::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
{
    std::ifstream input("../src/Scenario2.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-2 file ! \n";

    ll count;
    std::string name;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            readBird(name, birds);
            input >> name;
            birds[birds.size() - 1].setHomePlace(name);
        }
    }

    input.close();
}
void Scenario2::printOutput(Controler &control)
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