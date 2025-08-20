#ifndef ENEMY_H
#define ENEMY_H

#include "City.hpp"
#include "Bird.hpp"

#include <bits/stdc++.h>

class Enemy : public City
{
    public:
        virtual ~Enemy() = default;
        Enemy();
        Enemy(std::string name, ld x, ld y, bool is, int level);
        int getDefenseLevel();
        void setDefenseLevel(int defenseLevel);
        void pushReachBird(Bird bird);
        void setBirdPath(std::vector<std::shared_ptr<City>> & path);
        void clearReachBirds();
        std::vector<Bird> getReachBirds();

    private:
        int defenseLevel;
        std::vector<Bird> reachBirds; // the birds that reached the destination
};

#endif