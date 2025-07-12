#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>
#include "Bird.hpp"

class Scenario {

    public:
        void readOurBirds(); // read the birds we have in each scenario


    private:
        std::vector<Bird> birds;


};

#endif