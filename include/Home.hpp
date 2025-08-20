#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : public City
{
    public:
        virtual ~Home() = default;
        Home();
        Home(std::string name, ld x, ld y, bool is, int cap);
        int getCapacity();
        std::vector<Bird> & getMyBirds();
        void setCapacity(int capacity);
        void push(Bird & bird);
        void del(std::vector<Bird>::iterator it);
        void reduceCapacity();

    private:
        int capacity;
        std::string name;
        std::vector<Bird> myBirds;
};

#endif