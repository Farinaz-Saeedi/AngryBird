#ifndef SCENARIO7_H
#define SCENARIO7_H

#include <bits/stdc++.h>

#include "Scenario.hpp"
#include "Controler.hpp"

#define ld long double

struct OptionScenario7
{
    Bird *bird;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    ld expectedDamage;
    ld cost;
    ld radarLevel;
};

class Scenario7 : public Scenario
{
public:
    void readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes) override;
    void printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes) override;
    void setNumberOfNights(int numberOfNights);
    int getNumberOfNights();
    ld getDamage();
    void setDamage(ld damage);

private:
    int numberOfNights;
    ld damage;
    std::vector<std::pair<std::string, ld>> lst;
};

#endif