#include "Enemy.hpp"

Enemy::Enemy() {};

Enemy::Enemy(std::string name, ld x, ld y, bool is)
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
void Enemy::pushReachBird(Bird bird)
{
    reachBirds.push_back(bird);
}
std::vector<Bird> Enemy::getReachBirds()
{
    return reachBirds;
}
void Enemy::setIsFull(bool isFull)
{
    this->isFull = isFull;
}
bool Enemy::getIsFull()
{
    return isFull;
}