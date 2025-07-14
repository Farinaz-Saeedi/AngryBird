#include <bits/stdc++.h>

#include "Home.hpp"

Home::Home(){};

Home::Home(int cap)
{
    setCapacity(cap);
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