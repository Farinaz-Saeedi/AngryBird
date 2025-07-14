#include <bits/stdc++.h>

#include "Home.hpp"

Home::Home() {};

Home::Home(std::string nm, int cap)
{
    setCapacity(cap);
    setName(nm);
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
std::string Home::getName()
{
    return name;
}
void Home::setName(std::string name)
{
    this->name = name;
}