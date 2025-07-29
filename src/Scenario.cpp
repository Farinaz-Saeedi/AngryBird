#include <bits/stdc++.h>

#include "Scenario.hpp"

Bird Scenario::readBird(std::string targetName, std::vector<Bird> &birds)
{
    std::ifstream input("../src/Birds.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Birds file ! \n";

    std::string line;

    while (std::getline(input, line))
    {
        std::string name, temp;
        ll dist, out, demol;
        int degree, count;
        Type t;
        std::istringstream iss(line);
        if (iss >> name >> dist >> out >> degree >> demol >> t)
        {
            if (name == targetName)
            {
                input.close();

                Bird bird = Bird(name, dist, out, degree, demol, t);
                birds.push_back(bird);
                return bird;
            }
        }
    }
    return {};
}