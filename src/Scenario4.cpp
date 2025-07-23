#include "Scenario4.hpp"

void Scenario4::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
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
           readBird(name , birds);

           input >> name;
           birds[birds.size()-1].setHomePlace(name);
        }
    }

    input.close();
}