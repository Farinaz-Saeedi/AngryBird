#include "Scenario6.hpp"

void Scenario6::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
{
    std::ifstream input("Scenario6.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

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