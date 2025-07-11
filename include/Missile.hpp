#ifndef MISSILE_H
#define MISSILE_H

#include <string>
#include <fstream>

#define ll long long

enum Type {
    A , B , C , D
};

class Missile
{
    public:
        ll getDistance();
        ll getOutOfControl();
        ll getDemolition();
        int getDegree();
        Type getType();
        void setDistance(ll distance);
        void setOutOfControl(ll outOfControl);
        void setDemolition(ll demolition);
        void setDegree(int degree);
        void setType(Type type);

    private:
        ll distance;
        ll outOfControl;
        ll demolition;
        int degree;
        Type type;

};








#endif