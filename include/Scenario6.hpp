#ifndef SCENARIO6_H
#define SCENARIO6_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario6 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
       

    private:
       

};


#endif 