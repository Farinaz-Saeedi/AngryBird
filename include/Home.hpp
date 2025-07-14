#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : City {

    public:
        Home();
        Home(int cap);
        int getCapacity();
        void setCapacity(int capacity);

    private:
        int capacity;
       // std::vector<Bird> slingshot;

};

#endif