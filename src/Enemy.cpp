#include "Enemy.hpp"

Enemy::Enemy() {};

Enemy::Enemy(std::string name, ll x, ll y, bool is)
{
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
}
void Enemy::setDefenseLevel(int defenseLevel)
{
    this->defenseLevel = defenseLevel;
}
int Enemy::getDefenseLevel()
{
    return defenseLevel;
}