#include "Scenario2.hpp"

void Scenario2::readInputs(std::vector<Bird> & birds)
{
    std::ifstream input("Scenario2.txt");
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
        }
    }

    input.close();
}