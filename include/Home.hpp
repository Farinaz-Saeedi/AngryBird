#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : City {

    public:
        Home();
        Home(std::string nm, int cap);
        int getCapacity();
        void setCapacity(int capacity);
        void setName(std::string name);
        std::string getName();

    private:
        int capacity;
        std::string name;
       // std::vector<Bird> slingshot;

};

#endif