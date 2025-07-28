#ifndef SCENARIO7_H
#define SCENARIO7_H

#include <bits/stdc++.h>

#include "Scenario.hpp"
#include "Controler.hpp"

#define ld long double

class Scenario7 : public Scenario
{
public:
    void readInputs(std::vector<Bird> &birds, std::vector<Home> &homes) override;
    void printOutput(Controler & control) override;
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