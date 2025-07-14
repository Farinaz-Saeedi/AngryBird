#include <bits/stdc++.h>

#include "Scenario.hpp"

void Scenario::readBird(std::string targetName , std::vector<Bird> & birds)
{
    std::ifstream input("birds.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    std::string line;

    while (std::getline(input, line)) 
    {
        std::string name , temp ;
        ll dist , out , demol ; 
        int degree , count ;
        Type t;
        std::istringstream iss(line);
        if (iss >> name >> dist >> out >> degree >> demol >> t) {
            if (name == targetName) {
                input.close();
                birds.push_back(Bird(name , dist , out , degree , demol , t));
            }
        }
    }
}

// std::vector<Bird> Scenario::getBirds()
// {
//     return birds;
// }
// void Scenario::setBirds(std::vector<Bird> birds)
// {
//     this->birds = birds;
// }