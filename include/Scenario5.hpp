#ifndef SCENARIO5_H
#define SCENARIO5_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario5 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds, std::vector<Home> & homes) override;
        void printOutput(Controler & control) override;
        void setNumberOfNights(int numberOfNights);
        int getNumberOfNights();

    private:
        int numberOfNights;

};


#endif 