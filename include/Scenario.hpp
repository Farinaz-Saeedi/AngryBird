#ifndef SCENARIO_H
#define SCENARIO_H

#include <bits/stdc++.h>
#include "Bird.hpp"
#include "Home.hpp"

class Scenario {

    public:
        virtual void readInputs(std::vector<Bird> & birds, std::vector<Home> & homes) = 0; // read the birds we have in each scenario
        virtual void readBird(std::string targetName , std::vector<Bird> & birds);
        virtual ~Scenario() = default;


    private:


};

#endif