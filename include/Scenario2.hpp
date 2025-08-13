#ifndef SCENARIO2_H
#define SCENARIO2_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario2 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes, std::vector<Bird> &birds) override;

    private:
};

#endif