#include "Scenario3.hpp"


void Scenario3::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
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