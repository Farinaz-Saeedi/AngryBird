#ifndef SCENARIO3_H
#define SCENARIO3_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct Option {
    int birdIdx;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ld cost;

    Option(int b , std::shared_ptr<City> h , std::shared_ptr<City> t , std::vector<std::shared_ptr<City>> p , ld c)
    : birdIdx(b), home(h), target(t), path(p), cost(c) {}
};

class Scenario3 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes, std::vector<Bird> &birds) override;
        void setSlingshot(int number);
        int getSlingshot();
        std::vector<Option> assignOptions(Controler & controler , std::vector<std::shared_ptr<City>> & homes);   
        std::vector<int> hungarianMin(const std::vector<std::vector<ll>> & profitMatrix);
        std::vector<std::vector<ll>> buildProfitMatrix(Controler & controler);




    private:
        int numberOfSlingshot;
        std::vector<Option> options;
        std::vector<Option> finalOptions;
         std::vector<std::shared_ptr<Home>> myHomes;
};


#endif 