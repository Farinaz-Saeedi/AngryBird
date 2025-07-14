#ifndef SCENARIO2_H
#define SCENARIO2_H

#include "Scenario.hpp"

class Scenario2 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> &birds, std::vector<Home> &homes) override;

    private:
};

#endif