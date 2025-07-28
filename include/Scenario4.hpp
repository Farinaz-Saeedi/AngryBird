#ifndef SCENARIO4_H
#define SCENARIO4_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario4 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds, std::vector<Home> & homes) override;
        void printOutput(Controler & control) override;


    private:

};


#endif 