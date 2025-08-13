#ifndef SCENARIO_H
#define SCENARIO_H

#include <bits/stdc++.h>
#include "Bird.hpp"
#include "Home.hpp"

class Controler;

class Scenario {

    public:
        virtual void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) = 0; // read the birds we have in each scenario
        virtual Bird readBird(std::string targetName , std::vector<Bird> & birds);
        virtual void printOutput(Controler & control , std::vector<std::shared_ptr<City>> & homes, std::vector<Bird> &birds) = 0;
        virtual ~Scenario() = default;


    private:


};

#endif