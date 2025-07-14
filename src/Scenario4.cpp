#include "Scenario4.hpp"

void Scenario4::readInputs(std::vector<Bird> & birds)
{
    std::ifstream input("Scenario4.txt");
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
            if (str.find('A'))
            {
                bType = A;
            }
            else if (str.find('B'))
            {
                bType = B;
            }
            else if (str.find('C'))
            {
                bType = C;
            }
            
            getBirds()[i].setType(bType);
        }
    }

    input.close();
}