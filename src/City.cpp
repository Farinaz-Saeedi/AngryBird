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
std::string City::getCountryName()
{
    return countryName;
}
std::string City::getStatus()
{
    return status;
}

void City::setCountryName(std::string countryName)
{
    this->countryName = countryName;
}
void City::setStatus(std::string status)
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