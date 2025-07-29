#include <bits/stdc++.h>

#include "Home.hpp"

Home::Home() {}

Home::Home(std::string name, ld x, ld y, bool is, int cap)
{
    setCapacity(cap);
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
}
int Home::getCapacity()
{
    return capacity;
}
void Home::setCapacity(int capacity)
{
    this->capacity = capacity;
}
void Home::setCoordinates(ld newX, ld newY)
{
    setX(newX);
    setY(newY);
}
void Home::push(Bird &bird)
{
    myBirds.push_back(bird);
}
std::vector<Bird> &Home::getMyBirds()
{
    return myBirds;
}
void Home::del(std::vector<Bird>::iterator it)
{
    myBirds.erase(it);
}