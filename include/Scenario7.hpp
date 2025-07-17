#ifndef SCENARIO7_H
#define SCENARIO7_H

#include <bits/stdc++.h>

#include "Scenario.hpp"

#define ld long double

class Scenario7 : public Scenario
{
    public:
        void readInputs(std::vector<Bird> & birds, std::vector<Home> & homes) override;
        void setNumberOfNights(int numberOfNights);
        int getNumberOfNights();

    private:
        int numberOfNights;
        std::vector<std::pair<std::string , ld>> lst;

};


#endif 