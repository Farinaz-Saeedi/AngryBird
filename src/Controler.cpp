#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler()
{
    birds.resize(8);
    cities.resize(getNumberOfCities());
}

ll Controler::getNumberOfCities()
{
    return numberOfCities;
}
ll Controler::calDistance(City a, City b)
{
    ll yPow = pow((a.getY() - b.getY()), 2);
    ll xPow = pow((a.getX() - b.getX()), 2);
    return sqrt(yPow + xPow);
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
void Controler::setNumberOfCities(ll numberOfCities)
{
    this->numberOfCities = numberOfCities;
}
void Controler::makeGraph()
{
    for (int i{}; i < cities.size(); ++i)
    {
        for (int j{i + 1}; j < cities.size(); ++j)
        {
            // ld dist = calDistance(cities[i], cities[j]);
            graph[cities[i].getCountryName()].insert(cities[j].getCountryName());
            // if (graph[cities[i].getCountryName()].find(cities[j].getCountryName()) == graph[cities[i].getCountryName()].end())
            // {
            //     graph[cities[i].getCountryName()][cities[j].getCountryName()] = dist;
            // }
        }
    }
}
void Controler::sortCities()
{
    sort(cities.begin(), cities.end(), [](City &a, City &b)
         { return a.getX() > b.getX(); });
}
