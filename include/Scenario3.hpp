#ifndef SCENARIO3_H
#define SCENARIO3_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen3 // store a flight option for the bird
{
    int birdIdx;
    std::shared_ptr<City> home; // pointer to the bird's home city
    std::shared_ptr<City> target; // Pointer to the target city (enemy)
    std::vector<std::shared_ptr<City>> path; // The path from home to target
    ld cost; //the total cost of this option

    // Constructor to initialize all fields
    OptionScen3(int b , std::shared_ptr<City> h , std::shared_ptr<City> t , std::vector<std::shared_ptr<City>> p , ld c)
    : birdIdx(b), home(h), target(t), path(p), cost(c) {}
};

class Scenario3 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> & homes) override;
        std::vector<OptionScen3> assignOptions(Controler & controler , std::vector<std::shared_ptr<City>> & homes);   
        std::vector<int> hungarianMin(const std::vector<std::vector<ll>> & profitMatrix); // computes the optimal assignment to minimize total cost using the Hungarian algorithm
        std::vector<std::vector<ll>> buildProfitMatrix(Controler & controler); // creating a profit matrix that shows the assignment cost of each bird to each target

    private:
        std::vector<OptionScen3> options;

};


#endif 