#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler()
{
    missiles.resize(8);
    cities.resize(getNumberOfCities());
}

void Controler::readMissiles()
{
    std::ifstream input("Missiles.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    std::string str;
    ll number;
    Type mType;

    while (!input.eof())
    {
        for (int i = 0; i < 8; i++)
        {
            input >> str;
            missiles[i].setName(str);

            input >> number;
            missiles[i].setDistance(number);

            input >> number;
            missiles[i].setOutOfControl(number);

            input >> number;
            missiles[i].setDegree(number);

            input >> number;
            missiles[i].setDemolition(number);

            input >> str;

            if (str.find('A'))
            {
                mType = A;
            }
            else if (str.find('B'))
            {
                mType = B;
            }
            else if (str.find('C'))
            {
                mType = C;
            }
            else if (str.find('D'))
            {
                mType = D;
            }

            missiles[i].setType(mType);
        }
    }
    input.close();
}

void Controler::readCities()
{
    std::ifstream input("Cities.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    ll count, position;
    std::string str;
    bool spy;
    Status cStatus;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str;
            cities[i].setCountryName(str);

            input >> position;
            cities[i].setX(position);

            input >> position;
            cities[i].setY(position);

           input >> str;

            if (str.find('N'))
            {
                cStatus = N;
            }
            else if (str.find('E'))
            {
                cStatus = E;
            }
            else if (str.find('H'))
            {
                cStatus = H;
            }
            cities[i].setStatus(cStatus);

            input >> spy;
            cities[i].setIsSpy(spy);
        }
    }
    input.close();
}

ll Controler::getNumberOfCities()
{
    return numberOfCities;
}
void Controler::setNumberOfCities(ll numberOfCities)
{
    this->numberOfCities = numberOfCities;
}