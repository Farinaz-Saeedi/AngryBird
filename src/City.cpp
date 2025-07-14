#include <iostream>

#include "City.hpp"

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