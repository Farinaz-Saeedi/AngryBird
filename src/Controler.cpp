#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler() {}

ll Controler::getNumberOfCities()
{
    return numberOfCities;
}
std::vector<Bird> &Controler::getBirds()
{
    return birds;
}
ll Controler::calDistance(City a, City b)
{
    ll yPow = pow((a.getY() - b.getY()), 2);
    ll xPow = pow((a.getX() - b.getX()), 2);
    return sqrt(yPow + xPow);
}
void Controler::readCities()
{
    std::ifstream input("../src/Cities.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Cities file ! \n";

    ll count;
    ld x, y;
    std::string str, situation;
    bool spy;
    
    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; ++i)
        {
            input >> str >> x >> y >> situation >> spy;
            
            if (situation == "Normal")
            {
                auto city = std::make_shared<City>(str, x, y, spy);
                city->setStatus(N);
                cities.push_back(city);
            }
            else if (situation == "Enemy")
            {
                int level;
                input >> level;
                
                auto city = std::make_shared<Enemy>(str, x, y, spy, level);
                city->setStatus(E);
                cities.push_back(city);
                goalCities.push_back(city);
            }
            else if (situation == "Home")
            {
                int capacity;
                input >> capacity;

                auto city = std::make_shared<Home>(str, x, y, spy, capacity);
                city->setStatus(H);
                cities.push_back(city);
                startCities.push_back(city);
            }
        }
    }
    input.close(); 
}
void Controler::setNumberOfCities(ll numberOfCities)
{
    this->numberOfCities = numberOfCities;
}
std::shared_ptr<Scenario> Controler::readScenario(int scen)
{
    std::shared_ptr<Scenario> scenario;
    if (scen == 1)
    {
        scenario = std::make_shared<Scenario1>();
    }
    else if (scen == 2)
    {
        scenario = std::make_shared<Scenario2>();
    }
    else if (scen == 3)
    {
        scenario = std::make_shared<Scenario3>();
    }
    else if (scen == 4)
    {
        scenario = std::make_shared<Scenario4>();
    }
    else if (scen == 5)
    {
        scenario = std::make_shared<Scenario5>();
    }
    else if (scen == 6)
    {
        scenario = std::make_shared<Scenario6>();
    }
    else if (scen == 7)
    {
        scenario = std::make_shared<Scenario7>();
    }
    else
        std::cout << "WRONG NUMBER!";
    scenario->readInputs(birds, startCities);
    return scenario;
}
void Controler::run()
{
    readCities();

    std::ifstream input("../src/Scenario.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scenario file ! \n";

    int numberOfScen;
    input >> numberOfScen;
    std::shared_ptr<Scenario> whichScen = readScenario(numberOfScen);
    whichScen->printOutput(*this , startCities);
}
std::pair<std::string, bool> Controler::findBestPairFor(std::shared_ptr<City> & start , Bird & bird, std::vector<std::shared_ptr<City>> & path, ll & distance)
{
    int minSpies = INT_MAX;
    ld minCost = LDBL_MAX;
    std::shared_ptr<City> bestGoal = nullptr;
    std::vector<std::shared_ptr<City>> bestPath;
    ll bestDis;
    bool temp;

    for (auto & goal : goalCities) 
    {
        ld cost;
        temp = aStar(start->getCityName(), goal->getCityName(), bird, path, distance, cost); 
        if (!path.empty())
        {
            int spies = countSpiesOnPath(path);

            if (spies <= minSpies) 
            {
                if (cost < minCost) 
                {
                    minSpies = spies;
                    bestGoal = goal;
                    bestPath = path;
                    bestDis = distance;
                }
            } 
        } 
    }

    path = bestPath;
    distance = bestDis;
    if (bestGoal == nullptr)
        return {"", false};

    return {bestGoal->getCityName(), temp};
}
ld Controler::heuristic(City &a, City &b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}
bool Controler::aStar(std::string start, std::string goal, Bird myBird, std::vector<std::shared_ptr<City>> & path, ll & totalDistance, ld & cost)
{
    ll n = cities.size();
    
    std::unordered_map<std::string, int> nameToIndex;
    for (int i = 0; i < n; i++)
    {
        nameToIndex[cities[i]->getCityName()] = i;
    }
    
    if (start == goal)
    {
        path.clear();
        path.push_back(cities[nameToIndex[start]]);
        totalDistance = 0;
        return true;
    }

    int startIdx = nameToIndex[start];
    int goalIdx = nameToIndex[goal];
    ld hPenalty = cities[goalIdx]->getIsSpy() ? myBird.getOutOfControl() : 0.0;

    std::vector<ld> g(n, std::numeric_limits<ld>::infinity());
    std::vector<int> cameFrom(n, -1);

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
    std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>>
        openList([](std::shared_ptr<Node> a, std::shared_ptr<Node> b)
            { return a->fCost > b->fCost; });

    g[startIdx] = 0.0;
    auto startNode = std::make_shared<Node>();
    startNode->cityName = start;
    startNode->gCost = 0.0;
    startNode->fCost = heuristic(*cities[startIdx], *cities[goalIdx]);

    openList.push(startNode);

    while (!openList.empty())
    {
        auto current = openList.top();
        openList.pop();

        int u = nameToIndex[current->cityName];
        if (u == goalIdx)
        {
            cost = g[goalIdx];

            path.clear();
            int curr = goalIdx;
            totalDistance = 0.0;

            while (curr != -1)
            {
                path.push_back(cities[curr]);
                int prev = cameFrom[curr];
                if (prev != -1)
                {
                    totalDistance += heuristic(*cities[prev], *cities[curr]);
                }
                curr = prev;
            }
            std::reverse(path.begin(), path.end());

            if (!canDestroy(myBird, totalDistance))
                return false;
            
            return true;
        }

        for (int v = 0; v < n; ++v)
        {
            if (v == u) continue;

            ld dist = heuristic(*cities[u], *cities[v]);

            if (!canBirdReach(myBird, dist))
                continue;
            
            ld spyPenalty = cities[v]->getIsSpy() ? myBird.getOutOfControl() : 0.0;

            int defenseLvl = 0;
            if (cities[v]->getStatus() == E)
            {
                auto theEnemy = std::dynamic_pointer_cast<Enemy>(cities[v]);
                defenseLvl = theEnemy->getDefenseLevel();
            }
            ld defensePenalty = std::pow(defenseLvl * 10, 2);

            ld tempG = g[u] + dist + spyPenalty + defensePenalty;

            if (tempG < g[v])
            {
                g[v] = tempG;
                cameFrom[v] = u;

                auto neighborNode = std::make_shared<Node>();
                neighborNode->cityName = cities[v]->getCityName();
                neighborNode->gCost = tempG;
                neighborNode->fCost = tempG + heuristic(*cities[v], *cities[goalIdx]);

                openList.push(neighborNode);
            }
        }
    }
    return false;
}
bool Controler::canBirdReach(Bird &bird, ld distance)
{
    return bird.getOutOfControl() > distance;
}
bool Controler::canDestroy(Bird &bird, ld distance)
{
    if (bird.getDistance() >= 10000)
    {
        return true;
    }
    
    return bird.getDistance() >= distance;
}
bool Controler::isDetected(Bird &bird)
{
    int numberOfSpy = countSpiesOnPath(bird.getThePath());

    if (numberOfSpy >= bird.getDegree())
    {
        return true;
    }
    return false;
}
void Controler::shootDownBird(std::string enemyName) 
{
    std::shared_ptr<Enemy> enemy;
    for (auto & city : goalCities)
    {
        if (city->getCityName() == enemyName)
        {
            enemy = std::dynamic_pointer_cast<Enemy>(city);
        }
    }
    
    std::vector<Bird> detectedBirds;
    
    for (auto &it : enemy->getReachBirds())
    {
        if (isDetected(it))
        {
            detectedBirds.push_back(it);
        }
    }
    
    std::sort(detectedBirds.begin(), detectedBirds.end(), [](Bird a, Bird b)
    { return a.getDemolition() > b.getDemolition(); });
    
    std::unordered_map<std::string, std::vector<Bird>::iterator> birdMap;
    
    for (auto it = detectedBirds.begin(); it != detectedBirds.end(); it++)
    {
        birdMap[it->getName()] = it;
    }
    
    int range = std::min((int)detectedBirds.size(), enemy->getDefenseLevel());
    for (int i = 0; i < range ; i++)
    {
        std::cout << detectedBirds[i].getName() << " is destroyed by the enemies in [" << enemyName << "] \n";
        delBird(detectedBirds[i]);
    }
}
ld Controler::totoalDamage(std::vector<std::shared_ptr<City>> &path, Bird &bird)
{
    ld damage = 0.0;

    std::unordered_set<std::string> enemyCityNames;
    for (auto &goalCity : goalCities)
    {
        enemyCityNames.insert(goalCity->getCityName());
    }

    for (auto &city : path)
    {
        if (enemyCityNames.count(city->getCityName()))
        {
            damage += bird.getDemolition();
        }
    }
    return damage;
}
std::vector<std::shared_ptr<City>> Controler::getPath()
{
    return chosenPath;
}
int Controler::countSpiesOnPath(std::vector<std::shared_ptr<City>> path)
{
    int numberOfspies = 0;
    for ( auto & city : path )
    {
        if (city->getIsSpy())
            numberOfspies++;
    }
    return numberOfspies;
}
void Controler::newSpies(int targetNight)
{ 
    std::unordered_map<std::string , std::shared_ptr<City>> nameToCity;
    for (auto & city : cities)
    {
        nameToCity[city->getCityName()] = city;
    }

    std::ifstream input("../src/SpiesInScen5.txt");
    if (!input.is_open())
        std::cerr << " Unable to open SpiesInScen5 file ! \n";

    std::string line;
    while(std::getline(input , line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        int night;
        iss >> night;

        if (night != targetNight) continue;

        std::string cityName;
        while(iss >> cityName)
        {
            nameToCity[cityName]->setIsSpy(true);
        }
    }
}
void Controler::setReachBird(std::string enemyName, Bird &bird, std::vector<std::shared_ptr<City>> & path)
{
    std::shared_ptr<Enemy> enemy ;
    for (auto & city : goalCities)
    {
        if (city->getCityName() == enemyName)
        enemy = std::dynamic_pointer_cast<Enemy>(city);
    }
            
    if (enemy)
    {
        enemy->pushReachBird(bird);
        enemy->setBirdPath(path); 
    }
}
void Controler::attack()
{
    for (auto & goal : goalCities)
    {
        shootDownBird(goal->getCityName());
        auto enemy = std::dynamic_pointer_cast<Enemy>(goal);
        enemy->clearReachBirds();
    }
}
void Controler::delBird(Bird & bird)
{
    auto it = std::find(birds.begin(), birds.end(), bird);
    if (it != birds.end()) {
        birds.erase(it);
    }
}
void Controler::deadBird(Bird & myBird , ll & totalDistance)
{

    auto it = std::find(birds.begin(), birds.end(), myBird);
    if (it != birds.end())
    {
        birds.erase(it);
        std::cout << "\nTOTAL DISTANCE: " << totalDistance << " | RANGE: " << myBird.getDistance() << "\n";
        std::cout << myBird.getName() << " is dead in the path! \n" ;  
    }
}
std::vector<std::shared_ptr<City>> Controler::getEnemies()
{
    return goalCities;
}
int Controler::getBirdIdx(Bird & bird)
{
     auto it = std::find(birds.begin(), birds.end(), bird);

    if (it != birds.end())
    {
        int index = std::distance(birds.begin(), it);
        return index;
    } else 
    {
        return -1;
    }
}
std::shared_ptr<Enemy> Controler::getWeakEnemy()
{
    int min = INT_MAX ;
    std::shared_ptr<Enemy> weakest ;
    for (auto & city : goalCities)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(city);
        if ( enemy->getDefenseLevel() < min )
        {
            min = enemy->getDefenseLevel();
            weakest = enemy ;
        }
    }
    return weakest ;
}