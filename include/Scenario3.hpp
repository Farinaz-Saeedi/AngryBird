#ifndef SCENARIO3_H
#define SCENARIO3_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct OptionScen3 {
    int birdIdx;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ld cost;

    OptionScen3(int b , std::shared_ptr<City> h , std::shared_ptr<City> t , std::vector<std::shared_ptr<City>> p , ld c)
    : birdIdx(b), home(h), target(t), path(p), cost(c) {}
};

class Scenario3 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
        void setSlingshot(int number);
        int getSlingshot();
        std::vector<OptionScen3> assignOptions(Controler & controler , std::vector<std::shared_ptr<City>> & homes);   
        std::vector<int> hungarianMin(const std::vector<std::vector<ll>> & profitMatrix);
        std::vector<std::vector<ll>> buildProfitMatrix(Controler & controler);




    private:
        int numberOfSlingshot;
        std::vector<OptionScen3> options;
        std::vector<OptionScen3> finalOptions;
         std::vector<std::shared_ptr<Home>> myHomes;
};


#endif 