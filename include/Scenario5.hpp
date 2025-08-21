#ifndef SCENARIO5_H
#define SCENARIO5_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen5 // store a flight option for the bird
{
    int birdIdx;
    int spyNum; // number of spies in the path
    std::shared_ptr<City> home; // pointer to the bird's home city
    std::shared_ptr<City> target; // Pointer to the target city (enemy)
    std::vector<std::shared_ptr<City>> path; // The path from home to target
    ll damage; 

    OptionScen5(int b, int num, std::shared_ptr<City> h, std::shared_ptr<City> t,std::vector<std::shared_ptr<City>> p, ll dmg)
        : birdIdx(b), spyNum(num), home(h), target(t), path(p), damage(dmg) {}
};

class Scenario5 : public Scenario
{
public:
    void readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes) override;
    void printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes) override;
    void setNumberOfNights(int numberOfNights);
    int getNumberOfNights();

private:
    int numberOfNights;
    std::vector<OptionScen5> firstOptions; // birds which definitely reach their target
    std::vector<OptionScen5> allOptions; // all possible options
    std::vector<int> birdsToRemove; // keep the indices of removed birds
};

#endif