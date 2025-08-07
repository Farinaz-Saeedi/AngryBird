#ifndef SCENARIO3_H
#define SCENARIO3_H

#include "Scenario.hpp"
#include "Controler.hpp"

struct AssignmentOption {
    Bird bird;
    std::shared_ptr<City> home;
    std::shared_ptr<City> target;
    std::vector<std::shared_ptr<City>> path;
    ll damage;

    AssignmentOption(Bird b , std::shared_ptr<City> h , std::shared_ptr<City> t , std::vector<std::shared_ptr<City>> p , ll d)
    : bird(b), home(h), target(t), path(p), damage(d) {}
};

class Scenario3 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes) override;
        void printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes) override;
        void setSlingshot(int number);
        int getSlingshot();
        std::vector<AssignmentOption> assignOptions(Controler & controler , std::vector<std::shared_ptr<City>> & homes);   
        std::vector<int> hungarianMaximize(const std::vector<std::vector<double>> & profitMatrix);



    private:
        int numberOfSlingshot;

};


#endif 