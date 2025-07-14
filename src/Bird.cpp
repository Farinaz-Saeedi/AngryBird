#include <iostream>

#include "Bird.hpp"


Bird::Bird(){}
Bird::Bird(ll dis, ll out, ll dem, int deg, std::string name, Type t)
{
    setDistance(dis);
    setOutOfControl(out);
    setDemolition(dem);
    setDegree(deg);
    setName(name);
    setType(t);
}

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