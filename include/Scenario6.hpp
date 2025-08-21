#ifndef SCENARIO6_H
#define SCENARIO6_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen6
{
    int birdId;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ll damage;
    ld distance = 0.0;
    double survProb;

    OptionScen6(int b, std::shared_ptr<City> h, std::shared_ptr<City> t,std::vector<std::shared_ptr<City>> p, ll dmg, ld dis, double prob)
        : birdId(b), home(h), target(t), path(p), damage(dmg), distance(dis), survProb(prob) {}
};

class Scenario6 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
        void giveBirdsID();
        int getBirdIndex(int id);

       
    private:
        std::vector<OptionScen6> firstOptions;
        std::vector<int> birdsToRemove;
        std::vector<Bird> birds;

};


#endif 