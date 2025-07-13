#include "Scenario2.hpp"

void Scenario2::readInputs(std::string fileName)
{
    std::ifstream input("Scenario2.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count, number;
    std::string str;
    Type bType;
    Base base;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str;
            getBirds()[i].setName(str);

            input >> number;
            getBirds()[i].setDistance(number);

            input >> number;
            getBirds()[i].setOutOfControl(number);

            input >> number;
            getBirds()[i].setDegree(number);

            input >> number;
            getBirds()[i].setDemolition(number);

            input >> str;
            bType = A;
            getBirds()[i].setType(bType);

            input >> str;
            if (str.find('N'))
            {
                base = N;
            }
            else if (str.find('E'))
            {
                base = E;
            }
            else if (str.find('H'))
            {
                base = H;
            }

            getBirds()[i].setBase(base);
        }
    }

    input.close();
}