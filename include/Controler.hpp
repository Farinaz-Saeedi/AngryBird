#ifndef CONTROLER_H
#define CONTROLER_H

#include "Missile.hpp"
#include "City.hpp"

#define ll long long


#include <vector>


class Controler
{
    public:
        Controler();
        void readMissiles();
        void readCities();
        ll getNumberOfCities();
        void setNumberOfCities(ll numberOfCities);


    private:
        std::vector<Missile> missiles;
        std::vector<City> cities;
        ll numberOfCities;

};






#endif