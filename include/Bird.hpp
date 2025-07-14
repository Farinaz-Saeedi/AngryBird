#ifndef MISSILE_H
#define MISSILE_H

#include <string>

#define ll long long

enum Type {
    A , B , C , D
};

std::istream & operator>>(std::istream & is, Type & type);

class Bird
{
    public:
        Bird();
        Bird(std::string name, ll dis, ll out, int deg, ll dem, Type t);
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