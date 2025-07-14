#include "Scenario3.hpp"

void Scenario3::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
{
    std::ifstream input("Scenario3.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count, number;
    std::string name;
    int cp;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> cp;

            readHome(name, cp, homes);
        }
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