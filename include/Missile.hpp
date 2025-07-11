#ifndef MISSILE_H
#define MISSILE_H

#include <string>

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
        std::string getName();
        Type getType();
        void setDistance(ll distance);
        void setOutOfControl(ll outOfControl);
        void setDemolition(ll demolition);
        void setDegree(int degree);
        void setName(std::string name);
        void setType(Type type);

    private:
        ll distance;
        ll outOfControl;
        ll demolition;
        int degree;
        std::string name;
        Type type;

};








#endif