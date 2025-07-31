#include "Enemy.hpp"

Enemy::Enemy() {};

Enemy::Enemy(std::string name, ld x, ld y, bool is, int level)
{
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
    setDefenseLevel(level);
    setIsReady(false);
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
void Enemy::setIsReady(bool isReady)
{
    this->isReady = isReady;
}
bool Enemy::getIsReady()
{
    return isReady;
}