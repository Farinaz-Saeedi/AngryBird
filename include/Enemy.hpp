#ifndef ENEMY_H
#define ENEMY_H

#include "City.hpp"
#include "Bird.hpp"

#include <bits/stdc++.h>

class Enemy : public City {

    public:
        Enemy();
        Enemy(std::string name, ld x, ld y, bool is, int level);
        virtual ~Enemy() = default;
        void setDefenseLevel(int defenseLevel);
        int getDefenseLevel();
        void pushReachBird(Bird bird);
        std::vector<Bird> getReachBirds();
        void setIsReady(bool isReady);
        bool getIsReady();
        void setBirdPath(std::vector<std::shared_ptr<City>> & path);

    private:
        int defenseLevel;
        std::vector<Bird> reachBirds;
        bool isReady;


};

#endif