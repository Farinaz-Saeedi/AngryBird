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

#include <vector>

#define ll long long
#define ld long double


struct Node // structure used for the A* pathfinding algorithm
{
    std::string cityName;
    ld gCost; // the actual cost of the path from the origin to this city
    ld fCost; // the estimated cost to reach the goal

    bool operator>(const Node & other) const // for use in a priority_queue, ensuring that the lowest fCost is always prioritized first
    {
        return fCost > other.fCost;
    }
};

class Controler
{
    public:
        Controler();
        ll getNumberOfCities();
        ll calDistance(City a , City b); // calculating the distance between two cities
        ld heuristic(City & a , City & b); // calculate the Euclidean distance between two cities (used as heuristic in A*)
        void readCities(); // reads city data from Cities.txt file and creates City, Enemy, and Home objects
        void setNumberOfCities(ll numberOfCities);
        void run();
        void shootDownBird(std::string enemyName); // simulate enemy shooting down detected birds based on defense level.
        void newSpies(int targetNight); // updating the status of spies
        void setReachBird(std::string enemyName, Bird &bird , std::vector<std::shared_ptr<City>> & path);// add a bird that reached a specific enemy and store its path
        void attack(); // shooting down birds and clearing the list of reached birds for each enemy city
        void delBird(Bird & bird); // remove the specified bird from the birds vector
        void deadBird(Bird & bird, ll & totalDistanc);
        bool aStar(std::string start , std::string goal, Bird myBird, std::vector<std::shared_ptr<City>> & path, ll & totalDistance, ld & cost);
        bool canBirdReach(Bird & bird , ld distance); // check if the bird can reach a target given its maximum range (out-of-control distance)
        bool canDestroy(Bird & bird , ld distance); // check if the bird can destroy a target at a given distance (total distance)
        bool isDetected(Bird & bird); // check if the bird is detected by spies along its path
        int countSpiesOnPath(std::vector<std::shared_ptr<City>> path); // calculate the number of spies on a specific path
        std::shared_ptr<Scenario> readScenario( int scen ); // creating an appropriate object for the specified scenario and reading the related information
        std::shared_ptr<Enemy> getWeakEnemy(); // returns the weakest enemy city (with the lowest defense level)
        std::vector<Bird> & getBirds();
        std::vector<std::shared_ptr<City>> getEnemies();
        std::pair<std::string, bool> findBestPairFor(std::shared_ptr<City> & start , Bird & bird, std::vector<std::shared_ptr<City>> & path, ll & distance);

    private:
        std::vector<Bird> birds;
        std::vector<std::shared_ptr<City>> cities;
        std::vector<std::shared_ptr<City>> goalCities;
        std::vector<std::shared_ptr<City>> startCities;
        ll numberOfCities;
};

#endif