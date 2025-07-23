#include "Scenario2.hpp"

void Scenario2::readInputs(std::vector<Bird> & birds, std::vector<Home> & homes)
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
           readBird(name , birds);
           input >> name;
           birds[birds.size()-1].setHomePlace(name);
        }
    }

    input.close();
}