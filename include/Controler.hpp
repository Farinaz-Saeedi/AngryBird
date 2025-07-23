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

struct Node {
    std::string cityNamee;
    double gCost; 
    double fCost; 

    bool operator>(const Node & other) const 
    {
        return fCost > other.fCost;
    }
};

class Controler
{
    public:
        Controler();
        ll getNumberOfCities();
        ll calDistance(City a, City b);
        void readCities();
        void setNumberOfCities(ll numberOfCities);
        void sortCities(); // sort cities based on X
        void readScenario( int scen ); // read each scenario
        void run();
        std::pair<std::string, std::string> findBestPair();
        ld heuristic(City & a, City & b);
        std::vector<std::string> aStar(std::string start, std::string goal, ld maxDistance);
        bool canBirdReach(Bird & bird , ld distance);

    private:
        std::vector<Bird> birds;
        std::vector<Home> homes;
        std::vector<std::unique_ptr<City>> cities;
        std::vector<std::unique_ptr<City>> startCities;
        std::vector<std::unique_ptr<City>> goalCities;
        ll numberOfCities;
};

#endif