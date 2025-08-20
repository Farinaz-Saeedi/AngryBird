#include "City.hpp"

City::City(){}
City::City(std::string name, ld x, ld y, bool is)
{
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
}
ld City::getX()
{
    return x;
}
ld City::getY()
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
void City::setX(ld x)
{
    this->x = x;
}
void City::setY(ld y)
{
    this->y = y;
}
void City::setIsSpy(bool isSpy)
{
    this->isSpy = isSpy;
}