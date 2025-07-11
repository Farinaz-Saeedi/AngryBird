#include <iostream>

#include "Missile.hpp"


long long Missile::getDistance()
{
    return distance;
}
long long Missile::getOutOfControl()
{
    return outOfControl;
}
long long Missile::getDemolition()
{
    return demolition;
}
int Missile::getDegree()
{
    return degree;
}
std::string Missile::getName()
{
    return name;
}
Type Missile::getType()
{
    return type;
}

void Missile::setDistance(ll distance)
{
    this->distance = distance;
}
void Missile::setOutOfControl(ll outOfControl)
{
    this->outOfControl = outOfControl;
}
void Missile::setDemolition(ll demolition)
{
    this->demolition = demolition;
}
void Missile::setDegree(int degree)
{
    this->degree = degree;
}
void Missile::setType(Type type)
{
    this->type = type;
}
void Missile::setName(std::string name)
{
    this->name = name;
}

