#ifndef SCENARIO5_H
#define SCENARIO5_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen5
{
    int birdIdx;
    int spyNum;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ll damage;
    double survProb;

    OptionScen5(int b, int num, std::shared_ptr<City> h, std::shared_ptr<City> t,std::vector<std::shared_ptr<City>> p, ll dmg, double prob)
        : birdIdx(b), spyNum(num), home(h), target(t), path(p), damage(dmg), survProb(prob) {}
};

class Scenario5 : public Scenario
{
public:
    void readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes) override;
    void printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes) override;
    void setNumberOfNights(int numberOfNights);
    int getNumberOfNights();
    std::vector<int> hungarianMax(const std::vector<std::vector<ll>> &profit);

private:
    int numberOfNights;
    std::vector<OptionScen5> firstOptions;
    std::vector<OptionScen5> allOptions;
    std::vector<int> birdsToRemove;
};

#endif