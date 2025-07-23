#include "Scenario1.hpp"

void Scenario1::readInputs(std::vector<Bird> & birds,  std::vector<Home> & homes)
{
    std::ifstream input("../src/Scenario1.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-1 file ! \n";

    std::string name ;
    int count ;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            readBird(name , birds);
        }
    }

    input.close();
}
