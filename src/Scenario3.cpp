#include "Scenario3.hpp"

void Scenario3::readInputs()
{
    std::ifstream input("Scenario3.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count, number;
    std::string str;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str;
            input >> number;
            //setCityName(str);
            //setCapacit(number);     
        }
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str;
            input >> number;
            //setBirdName(str);
            //make birds in vector
        }
    }

    input.close();
}