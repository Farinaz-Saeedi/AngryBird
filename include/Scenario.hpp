#ifndef SCENARIO_H
#define SCENARIO_H

#include <bits/stdc++.h>
#include "Bird.hpp"
#include "Home.hpp"

class Scenario {

    public:
        virtual void readInputs(std::vector<Bird> & birds) = 0; // read the birds we have in each scenario
        virtual void readBird(std::string targetName , std::vector<Bird> & birds);
        virtual void readHome(std::string homeName, int cap, std::vector<Home> & homes);
        virtual ~Scenario() = default;

        // std::vector<Bird> getBirds();
        // void setBirds(std::vector<Bird> birds);


    private:
        // std::vector<Bird> birds;


};

#endif