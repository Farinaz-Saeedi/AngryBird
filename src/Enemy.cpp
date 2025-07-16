#include "Enemy.hpp"

Enemy::Enemy() {};

Enemy::Enemy(std::string name, ll x, ll y, bool is)
{
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
}