#ifndef SCENARIO3_H
#define SCENARIO3_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario3 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds, std::vector<Home> & homes) override;
        void printOutput(Controler & control) override;
        void setSlingshot(int number);
        int getSlingshot();


    private:
        int numberOfSlingshot;

};


#endif 