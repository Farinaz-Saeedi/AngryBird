#ifndef MISSILE_H
#define MISSILE_H

#include <string>
#include <fstream>

class Missile
{
    public:
        long long getDistance();
        long long getOutOfControl();
        long long getDemolition();
        int getDegree();
        std::string getType();
        void readMissiles();

    private:
        long long distance;
        long long outOfControl;
        long long demolition;
        int degree;
        std::string type;

};








#endif