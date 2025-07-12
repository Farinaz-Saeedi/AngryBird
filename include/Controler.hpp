#ifndef CONTROLER_H
#define CONTROLER_H

#include "Bird.hpp"
#include "City.hpp"

#define ll long long


#include <vector>


class Controler
{
    public:
        Controler();
        ll getNumberOfCities();
        ll calDistance(City a , City b);
        void readBirds();
        void readCities();
        void setNumberOfCities(ll numberOfCities);
        void makeGraph();
        void sortCities(); // sort cities based on X


    private:
        std::vector<Bird> birds;
        std::vector<City> cities;
        ll numberOfCities;
        std::unordered_map<std::string , std::unordered_set<std::string>> graph;


};



#endif