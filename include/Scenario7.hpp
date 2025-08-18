#ifndef SCENARIO7_H
#define SCENARIO7_H

#include <bits/stdc++.h>

#include "Scenario.hpp"
#include "Controler.hpp"
#include "Enemy.hpp"
#include "Bird.hpp"

#define ld long double

struct OptionScen7
{
    int birdId;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ll damage;
    ld cost;
    ll distance;
    int radarLevel;
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
    void giveBirdsID();
    int getBirdIndex(int id);

    std::vector<OptionScen7> knapsackMinCost(const std::vector<OptionScen7> &options, ld targetDamage, int maxBirds);

private:
    int numberOfNights;
    ld damage;
    std::vector<std::pair<std::string, ld>> lst;
    std::vector<OptionScen7> options;
    ld getBirdCost(const std::string &birdName);
    std::vector<Bird> birds;
};

#endif