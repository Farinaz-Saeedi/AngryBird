#ifndef BIRD_H
#define BIRD_H

#include <bits/stdc++.h>
#include "City.hpp"

#define ll long long

enum Type {
    A , B , C , D
};

std::istream & operator>>(std::istream & input, Type & type);

class Bird
{
    friend std::istream & operator>>(std::istream & input, Type & type);
    public:
        bool operator==(const Bird & other);
        Bird();
        Bird(std::string name, ll dis, ll out, int deg, ll dem, Type t);
        ll getDistance();
        ll getOutOfControl();
        ll getDemolition();
        int getDegree();
        int getID();
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
        void setThePath(std::vector<std::shared_ptr<City>> &path);
        void setID(int id);
        std::vector<std::shared_ptr<City>> getThePath();

    private:
        ll distance;
        ll outOfControl;
        ll demolition;
        int degree;
        std::string name;
        std::string homePlace;
        Type type;
        std::vector<std::shared_ptr<City>> thePath;
        int ID;

};

#endif