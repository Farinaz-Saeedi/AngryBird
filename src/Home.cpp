#include <bits/stdc++.h>

#include "Home.hpp"

int Home::getCapacity()
{
    return capacity;
}

void Home::setCapacity(int cap)
{
    capacity = cap;
    slingshot.resize(capacity);
}