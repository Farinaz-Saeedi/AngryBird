#ifndef SCENARIO5_H
#define SCENARIO5_H

#include "Scenario.hpp"
#include "Controler.hpp"

class Scenario5 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
        void setNumberOfNights(int numberOfNights);
        int getNumberOfNights();
        std::vector<std::vector<Bird>>distributeBirds(Controler & control);

    private:
        int numberOfNights;

};


#endif 