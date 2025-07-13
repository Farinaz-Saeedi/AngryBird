#ifndef SCENARIO_H
#define SCENARIO_H

#include <bits/stdc++.h>
#include "Bird.hpp"

class Scenario {

    public:
        virtual void readInputs(std::string fileName) = 0; // read the birds we have in each scenario
        virtual ~Scenario() = default;

        std::vector<Bird> getBirds();
        void setBirds( std::vector<Bird> birds);


    private:
        std::vector<Bird> birds;


};

#endif