#ifndef SCENARIO1_H
#define SCENARIO1_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario1 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds,std::vector<Home> & homes) override;
        void printOutput(Controler & control) override;

    private:

};






#endif 