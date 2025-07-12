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
        void readBirds();
        void readCities();
        ll getNumberOfCities();
        void setNumberOfCities(ll numberOfCities);


    private:
        std::vector<Bird> birds;
        std::vector<City> cities;
        ll numberOfCities;

};



#endif