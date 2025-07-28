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
void Scenario1::printOutput(Controler &control)
{
    ld totalDamage = 0.0;

    for (auto &bird : control.getBirds())
    {
        auto pair = control.getTopBestPair();
        if (pair.first.empty() || pair.second.empty()) {
            std::cerr << "Invalid city pair!\n";
        
        }
        auto path = control.getPath(); 

        std::cout << "\nBird : " << bird.getName() << "\nPath: ";
        for (auto &city : path)
        {
            std::cout << city << " ";
        }
    }
        std::cout << "\n\n";
        //totalDamage += control.totoalDamage(path, bird);

    std::cout << "Total Damage: " << totalDamage << "\n";
}
