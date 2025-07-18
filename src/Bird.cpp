#include <iostream>

#include "Bird.hpp"


std::istream & operator>>(std::istream & input , Type & type)
{   
    std::string str;
    input >> str;
    if (str.find('A'))
    {
        type = A;
    }
    else if (str.find('B'))
    {
        type = B;
    }
    else if (str.find('C'))
    {
        type = C;
    }
    else if (str.find('D'))
    {
        type = D;
    }
}

Bird::Bird(){}
Bird::Bird(std::string name, ll dis, ll out, int deg, ll dem, Type t)
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