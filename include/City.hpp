#ifndef CITY_H
#define CITY_H

#include <string>

#define ll long long

class City
{
    public:
        std::string getCountryName();
        std::string getStatus();
        ll getX();
        ll getY();
        bool getIsSpy();

        void setCountryName(std::string countryName);
        void setStatus(std::string status);
        void setX(ll x);
        void setY(ll y);
        void setIsSpy(bool isSpy);

    private:
        std::string countryName;
        std::string status; // Normal city - Enemy city - Home base
        ll x;
        ll y;
        bool isSpy;
};

#endif