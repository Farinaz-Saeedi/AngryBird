#ifndef SCENARIO4_H
#define SCENARIO4_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario4 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> & homes) override;

};


#endif 