#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy() {};

Enemy::Enemy(std::string name, ld x, ld y, bool is, int level)
{
    setCityName(name);
    setX(x);
    setY(y);
    setIsSpy(is);
    setDefenseLevel(level);
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
void Enemy::setBirdPath(std::vector<std::shared_ptr<City>> & path)
{
    reachBirds.back().setThePath(path);
}
void Enemy::clearReachBirds()
{
    reachBirds.clear();
}