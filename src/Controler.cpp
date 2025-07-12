#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler()
{
    birds.resize(8);
    cities.resize(getNumberOfCities());
}

void Controler::readBirds()
{
    std::ifstream input("Birds.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    std::string str;
    ll number;
    Type bType;

    while (!input.eof())
    {
        for (int i = 0; i < 8; i++)
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
            else if (str.find('D'))
            {
                bType = D;
            }

            birds[i].setType(bType);
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