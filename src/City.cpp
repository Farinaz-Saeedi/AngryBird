#include <iostream>

#include "City.hpp"

City::City(){}
City::City(std::string name, Status st, ll x, ll y, bool is)
{
    setCityName(name);
    setStatus(st);
    setX(x);
    setY(y);
    setIsSpy(is);
}

ll City::getX()
{
    return x;
}
ll City::getY()
{
    return y;
}
bool City::getIsSpy()
{
    return isSpy;
}
std::string City::getCityName()
{
    return cityName;
}
Status City::getStatus()
{
    return status;
}

void City::setCityName(std::string countryName)
{
    this->cityName = countryName;
}
void City::setStatus(Status status)
{
    this->status = status;
}
void City::setX(ll x)
{
    this->x = x;
}
void City::setY(ll y)
{
    this->y = y;
}
void City::setIsSpy(bool isSpy)
{
    this->isSpy = isSpy;
}