#ifndef CONTROLER_H
#define CONTROLER_H

#include "Bird.hpp"
#include "Home.hpp"
#include "City.hpp"
#include "Scenario.hpp"
#include "Scenario1.hpp"
#include "Scenario2.hpp"
#include "Scenario3.hpp"
#include "Scenario4.hpp"
#include "Scenario5.hpp"
#include "Scenario6.hpp"
#include "Scenario7.hpp"
#include "Enemy.hpp"


#define ll long long
#define ld long double

#include <vector>

class Controler
{
    public:
        Controler();
        ll getNumberOfCities();
        ll calDistance(City a, City b);
        void readCities();
        void setNumberOfCities(ll numberOfCities);
        void makeGraph();
        void sortCities(); // sort cities based on X
        void readScenario( int scen ); // read each scenario
        void run();

    private:
        std::vector<Bird> birds;
        std::vector<Home> homes;
        std::vector<std::unique_ptr<City>> cities;
        ll numberOfCities;
        std::unordered_map<std::string, std::unordered_set<std::string>> graph;
        std::unordered_map<std::string, std::unordered_map<std::string, ld>> distBetween;
};

#endif