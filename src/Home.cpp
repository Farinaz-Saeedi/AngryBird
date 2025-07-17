#include <bits/stdc++.h>

#include "Home.hpp"

Home::Home() {};

Home::Home(std::string name, ll x, ll y, bool is, int cap)
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
    // slingshot.resize(capacity);
}
void Home::setCoordinates(ll newX, ll newY)
{
    setX(newX);
    setY(newY);
}