#ifndef SCENARIO_H
#define SCENARIO_H

#include "Bird.hpp"
#include "Home.hpp"

#include <bits/stdc++.h>

class Controler;

class Scenario
{
    public:
        virtual ~Scenario() = default;
        virtual Bird readBird(std::string targetName , std::vector<Bird> & birds); // read and store birds for the scenario  
        virtual void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) = 0; // read and store other inputs for the scenario 
        virtual void printOutput(Controler & control , std::vector<std::shared_ptr<City>> & homes) = 0;

    private:

};

#endif