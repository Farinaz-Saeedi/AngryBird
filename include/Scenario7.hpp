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
    std::shared_ptr<City> home; // pointer to the bird's home city
    std::shared_ptr<City> target;  // Pointer to the target city (enemy)
    std::vector<std::shared_ptr<City>> path; // The path from home to target
    ll damage;
    ld cost;
    ld distance;
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
    void giveBirdsID();  // Assign unique IDs to birds for safe removal
    int getBirdIndex(int id);

    std::vector<OptionScen7> knapsackMinCost(const std::vector<OptionScen7> &options, ld targetDamage, int maxBirds);
    // Knapsack function to select birds for minimum cost while reaching target damage

private:
    int numberOfNights;
    ld damage;
    std::vector<std::pair<std::string, ld>> lst; // Stores bird cost data
    std::vector<OptionScen7> options; // List of calculated options for the night
    ld getBirdCost(const std::string &birdName); // Retrieve the cost of a specific bird
    std::vector<Bird> birds;
};

#endif