#include <iostream>

#include "Bird.hpp"


long long Bird::getDistance()
{
    return distance;
}
long long Bird::getOutOfControl()
{
    return outOfControl;
}
long long Bird::getDemolition()
{
    return demolition;
}
int Bird::getDegree()
{
    return degree;
}
std::string Bird::getName()
{
    return name;
}
Type Bird::getType()
{
    return type;
}
Base Bird::getBase()
{
    return base;
}

void Bird::setDistance(ll distance)
{
    this->distance = distance;
}
void Bird::setOutOfControl(ll outOfControl)
{
    this->outOfControl = outOfControl;
}
void Bird::setDemolition(ll demolition)
{
    this->demolition = demolition;
}
void Bird::setDegree(int degree)
{
    this->degree = degree;
}
void Bird::setType(Type type)
{
    this->type = type;
}
void Bird::setName(std::string name)
{
    this->name = name;
}
void Bird::setBase(Base base)
{
    this->base = base;
}

