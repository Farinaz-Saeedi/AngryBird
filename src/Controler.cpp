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

    ll count;
    ld x, y;
    std::string str, situation;
    bool spy;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str >> x >> y >> situation >> spy;

            if (situation == "Normal")
            {
                auto city = std::make_unique<City>(str, x, y, spy);
                city->setStatus(N);
                cities.push_back(std::move(city));
            }
            else if (situation == "Enemy")
            {
                auto city = std::make_unique<Enemy>(str, x, y, spy);
                city->setStatus(E);
                cities.push_back(std::move(city));
                goalCities.push_back(std::move(city));
            }
            else if (situation == "Home")
            {
                int capacity;
                input >> capacity;

                auto city = std::make_unique<Home>(str, x, y, spy, capacity);
                city->setStatus(H);
                cities.push_back(std::move(city));
                startCities.push_back(std::move(city));
            }
        }
    }
    input.close();
}
void Controler::setNumberOfCities(ll numberOfCities)
{
    this->numberOfCities = numberOfCities;
}
void Controler::sortCities()
{
    sort(cities.begin(), cities.end(), [](City a, City b)
         { return a.getX() > b.getX(); });
}
void Controler::readScenario(int scen)
{
    if (scen == 1)
    {
        Scenario1 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 2)
    {
        Scenario2 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 3)
    {
        Scenario3 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 4)
    {
        Scenario4 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 5)
    {
        Scenario5 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 6)
    {
        Scenario6 scenario;
        scenario.readInputs(birds, homes);
    }
    else
    {
        Scenario7 scenario;
        scenario.readInputs(birds, homes);
    }
}
void Controler::run()
{
    int numberOfScen;

    std::ifstream input("Scenario.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    input >> numberOfScen;
    readScenario(numberOfScen);
}
std::pair<std::string, std::string> Controler::findBestPair()
{
    ld bestEstimate = std::numeric_limits<double>::infinity();
    std::pair<std::string, std::string> bestPair = {NULL , NULL};

    for (const auto& start : startCities) {
        for (const auto& goal : goalCities) {
            double estimate = heuristic(*start, *goal);
            if (estimate < bestEstimate) {
                bestEstimate = estimate;
                bestPair = {start->getCityName(), goal->getCityName()};
            }
        }
    }

    return bestPair;
}
ld Controler::heuristic(City & a, City & b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() + b.getY()),2));
}
