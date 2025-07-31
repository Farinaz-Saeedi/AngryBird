#ifndef ENEMY_H
#define ENEMY_H

#include "City.hpp"
#include "Bird.hpp"

#include <vector>

class Enemy : public City {

    public:
        Enemy();
        Enemy(std::string name, ld x, ld y, bool is);
        virtual ~Enemy() = default;
        void setDefenseLevel(int defenseLevel);
        int getDefenseLevel();
        void pushReachBird(Bird bird);
        std::vector<Bird> getReachBirds();
        void setIsReady(bool isFull);
        bool getIsReady();

    private:
        int defenseLevel;
        std::vector<Bird> reachBirds;
        bool isFull;


};

#endif