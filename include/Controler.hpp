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
    std::string cityName;
    ld gCost; 
    ld fCost; 

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
        ll calDistance(City a , City b);
        void readCities();
        void setNumberOfCities(ll numberOfCities);
        std::shared_ptr<Scenario> readScenario( int scen ); // read each scenario
        void run();
        std::pair<std::string, bool> findBestPairFor(std::shared_ptr<City> & start , Bird & bird, std::vector<std::shared_ptr<City>> & path, ll & distance);
        ld heuristic(City & a , City & b);
        bool aStar(std::string start , std::string goal, Bird myBird, std::vector<std::shared_ptr<City>> & path, ll & totalDistance, ld & cost);
        bool canBirdReach(Bird & bird , ld distance);
        bool canDestroy(Bird & bird , ld distance);
        bool isDetected(Bird & bird);
        void shootDownBird(std::string enemyName);
        ld totoalDamage(std::vector<std::shared_ptr<City>> & path , Bird & bird);
        std::vector<Bird> getBirds();
        std::vector<std::shared_ptr<City>> getPath();
        int countSpiesOnPath(std::vector<std::shared_ptr<City>> path);
        void newSpies();
        void setReachBird(std::string &enemyName, Bird &bird , std::vector<std::shared_ptr<City>> & path);
        void attack();
        void delBird(Bird & bird);
        void deadBird(Bird & bird, ll & totalDistanc);
        std::vector<std::shared_ptr<City>> getEnemies();



    private:
        std::vector<Bird> birds;
        // std::vector<std::shared_ptr<City>> homes;
        std::vector<std::shared_ptr<City>> cities;
        std::vector<std::shared_ptr<City>> goalCities;
        std::vector<std::shared_ptr<City>> startCities;
        std::vector<std::shared_ptr<City>> chosenPath;
       
        ll numberOfCities;
};

#endif