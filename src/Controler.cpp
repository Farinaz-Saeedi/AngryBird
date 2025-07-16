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
            cities[i]->setCityName(str);

            input >> position;
            cities[i]->setX(position);

            input >> position;
            cities[i]->setY(position);

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
            cities[i]->setStatus(cStatus);

            input >> spy;
            cities[i]->setIsSpy(spy);
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
            ld dist = calDistance(*cities[i], *cities[j]);
            graph[cities[i]->getCityName()].insert(cities[j]->getCityName());
            if (distBetween[cities[i]->getCityName()].find(cities[j]->getCityName()) == distBetween[cities[i]->getCityName()].end())
            {
                distBetween[cities[i]->getCityName()][cities[j]->getCityName()] = dist;
            }
        }
    }
}
void Controler::sortCities()
{
    sort(cities.begin(), cities.end(), [](City a, City b)
         { return a.getX() > b.getX(); });
}
 void Controler::readScenario(int scen)
 {
    if ( scen == 1 ) {
        Scenario1 scenario;
        scenario.readInputs(birds);
    } else if ( scen == 2 ) {
        Scenario2 scenario;
        scenario.readInputs(birds);
    } else if ( scen == 4 ) {
        Scenario4 scenario;
        scenario.readInputs(birds);
    } // else ...

 }
 void Controler::run()
 {
    int numberOfScen;
    int whichScen;

    std::ifstream input("Scenario.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    input >> numberOfScen;

    while ( numberOfScen-- )
    {
        input >> whichScen;
        readScenario(whichScen);
        // funtion to solve the scenarios
    }

 }