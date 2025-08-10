#ifndef SCENARIO5_H
#define SCENARIO5_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct Option
{
    int birdIdx;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ld cost;
    ll damage;
    double successProb;

    Option(int b, std::shared_ptr<City> h, std::shared_ptr<City> t,
           std::vector<std::shared_ptr<City>> p, long double c,
           long long dmg, double prob)
        : birdIdx(b), home(h), target(t), path(p), cost(c), damage(dmg), successProb(prob) {}
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
};

#endif