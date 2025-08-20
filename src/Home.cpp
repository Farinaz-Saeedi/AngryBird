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
void Home::push(Bird & bird)
{
    myBirds.push_back(bird);
}
void Home::del(std::vector<Bird>::iterator it)
{
    myBirds.erase(it);
}
void Home::reduceCapacity()
{
    capacity--;
}
std::vector<Bird> & Home::getMyBirds()
{
    return myBirds;
}