#ifndef SCENARIO6_H
#define SCENARIO6_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen6
{
    int birdId;
    std::shared_ptr<City> home; // pointer to the bird's home city
    std::shared_ptr<City> target; // Pointer to the target city (enemy)
    std::vector<std::shared_ptr<City>> path; // The path from home to target
    ll damage;

    OptionScen6(int b, std::shared_ptr<City> h, std::shared_ptr<City> t,std::vector<std::shared_ptr<City>> p, ll dmg)
        : birdId(b), home(h), target(t), path(p), damage(dmg) {}
};

class Scenario6 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
        void giveBirdsID(); // give an ID to all birds
        int getBirdIndex(int id); // get the index of a bird with its id

       
    private:
        std::vector<OptionScen6> firstOptions; // birds which definitely reach their target
        std::vector<int> birdsToRemove; // keep the indices of removed birds
        std::vector<Bird> birds; // all birds

};


#endif 