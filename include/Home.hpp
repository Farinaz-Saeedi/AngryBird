#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : City {

    public:
        int getCapacity();
        void setCapacity(int cap);

    private:
        int capacity;
        std::vector<Bird> slingshot;

};

#endif