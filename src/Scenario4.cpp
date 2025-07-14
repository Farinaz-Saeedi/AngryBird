#include "Scenario4.hpp"

void Scenario4::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
{
    std::ifstream input("Scenario4.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count;
    std::string name;
    int cp;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
           input >> name;
           readBird(name , birds);

           input >> name;
           input >> cp;
           readHome(name, cp, homes);
        }
    }

    input.close();
}