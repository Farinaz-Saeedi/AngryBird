#ifndef ENEMY_H
#define ENEMY_H

#include "City.hpp"

class Enemy : public City {

    public:
        Enemy();
        Enemy(std::string name, ll x, ll y, bool is);
        virtual ~Enemy() = default;
        void setDefenseLevel(int defenseLevel);
        int getDefenseLevel();
        // kill birds ...

    private:
        int defenseLevel;


};

#endif