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
        // ~Controler();
        ll getNumberOfCities();
        ll calDistance(City a, City b);
        void readCities();
        void setNumberOfCities(ll numberOfCities);
        std::shared_ptr<Scenario> readScenario( int scen ); // read each scenario
        void run();
        void findBestPairs();
        ld heuristic(City & a, City & b);
        void aStar(std::string start, std::string goal, Bird myBird);
        bool canBirdReach(Bird & bird , ld distance);
        bool canDestroy(Bird & bird , ld distance);
        bool isDetected(Bird & bird);
        void shootDownBird(Enemy &enemy);
        std::pair<std::string , std::string> getTopBestPair();
        ld totoalDamage(std::vector<std::string> &path, Bird & bird);
        std::vector<Bird> getBirds();


    private:
        std::vector<Bird> birds;
        std::vector<Home> homes;
        std::vector<std::shared_ptr<City>> cities;
        std::vector<std::shared_ptr<City>> goalCities;
        std::vector<std::shared_ptr<City>> startCities;
        std::vector<std::shared_ptr<City>> path;
        std::vector<std::pair<std::string , std::string>> bestPairs;
       
        ll numberOfCities;
};

#endif