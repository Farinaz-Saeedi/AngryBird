#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : public City {

    public:
        Home();
        Home(std::string name, ll x, ll y, bool is, int cap);
        virtual ~Home() = default;
        int getCapacity();
        void setCapacity(int capacity);
        void setCoordinates(ll newX, ll newY);

    private:
        int capacity;
        std::string name;
       // std::vector<Bird> slingshot;

};

#endif