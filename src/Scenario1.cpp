#include "Scenario1.hpp"

void Scenario::readInputs(std::string fileName)
{
    std::ifstream input("Scenario1.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count, number;
    std::string str;
    Type bType;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str;
            birds[i].setName(str);

            input >> number;
            birds[i].setDistance(number);

            input >> number;
            birds[i].setOutOfControl(number);

            input >> number;
            birds[i].setDegree(number);

            input >> number;
            birds[i].setDemolition(number);

            input >> str;
            bType = D;
            birds[i].setType(bType);
        }
    }

    input.close();
}
