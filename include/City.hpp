#ifndef CITY_H
#define CITY_H

#include <string>

#define ll long long

enum Status
{
    N, E, H
};

class City
{
    public:
        City();
        City(std::string name, Status st, ll x, ll y, bool is);
        std::string getCityName();
        Status getStatus();
        ll getX();
        ll getY();
        bool getIsSpy();

        void setCityName(std::string countryName);
        void setStatus(Status status);
        void setX(ll x);
        void setY(ll y);
        void setIsSpy(bool isSpy);

    private:
        std::string cityName;
        Status status; // Normal city - Enemy city - Home base
        ll x;
        ll y;
        bool isSpy;
};

#endif