#ifndef HOME_H
#define HOME_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Home : public City {

    public:
        Home();
        Home(std::string name, ld x, ld y, bool is, int cap);
        virtual ~Home() = default;
        int getCapacity();
        void setCapacity(int capacity);
        void setCoordinates(ld newX, ld newY);
        void push(Bird &bird);
        std::vector<Bird> getMyBirds();

    private:
        int capacity;
        std::string name;
        std::vector<Bird> myBirds;

};

#endif