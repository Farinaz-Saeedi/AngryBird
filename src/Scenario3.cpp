#include "Scenario3.hpp"


void Scenario3::readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes)
{
    std::ifstream input("../src/Scenario3.txt");
    if (!input.is_open())
    std::cerr << " Unable to open Scen-3 file ! \n";
    
    ll count, number;
    std::string name;

    while (!input.eof())
    {
        input >> count;
        setSlingshot(count);
        
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> number;
            for (int i = 0; i < number; i++)
            {
                readBird(name, birds);
            }
        }
    }
    
    input.close();
}
void Scenario3::setSlingshot(int number)
{
    numberOfSlingshot = number;
}
int Scenario3::getSlingshot()
{
    return numberOfSlingshot;
}
void Scenario3::printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes)
{
//     ld totalDamage = 0.0;

//     for (auto &bird : control.getBirds())
//     {
//         auto path = control.aStar(control.getTopBestPair().first, control.getTopBestPair().second, bird);

//         std::cout << "\nBird : " << bird.getName() << "\nPath: ";
//         for (auto &city : path)
//         {
//             std::cout << city << " ";
//         }

//         std::cout << "\n\n";
//         totalDamage += control.totoalDamage(path, bird);
//     }

//     std::cout << "Total Damage: " << totalDamage << "\n";
}