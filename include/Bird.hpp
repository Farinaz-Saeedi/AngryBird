#ifndef BIRD_H
#define BIRD_H

#include <string>

#define ll long long

enum Type {
    A , B , C , D
};

std::istream & operator>>(std::istream & input, Type & type);

class Bird
{
    friend std::istream & operator>>(std::istream & input, Type & type);
    public:
        Bird();
        Bird(std::string name, ll dis, ll out, int deg, ll dem, Type t);
        ll getDistance();
        ll getOutOfControl();
        ll getDemolition();
        int getDegree();
        std::string getName();
        std::string getHomePlace();
        Type getType();
        void setDistance(ll distance);
        void setOutOfControl(ll outOfControl);
        void setDemolition(ll demolition);
        void setDegree(int degree);
        void setName(std::string name);
        void setType(Type type);
        void setHomePlace(std::string homeName);

    private:
        ll distance;
        ll outOfControl;
        ll demolition;
        int degree;
        std::string name;
        std::string homePlace;
        Type type;

};

#endif