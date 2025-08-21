#include <bits/stdc++.h>

#include "Controler.hpp"

Controler::Controler() {}
ll Controler::getNumberOfCities()
{
    return numberOfCities;
}
ll Controler::calDistance(City a, City b) 
{
    ll yPow = pow((a.getY() - b.getY()), 2);
    ll xPow = pow((a.getX() - b.getX()), 2);
    return sqrt(yPow + xPow);
}
ld Controler::heuristic(City &a, City &b) 
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}
bool Controler::aStar(std::string start, std::string goal, Bird myBird, std::vector<std::shared_ptr<City>> & path, ld & totalDistance, ld & cost)
{
    ll n = cities.size(); // get the total number of cities
    
    std::unordered_map<std::string, int> nameToIndex; // map city names to their indices for quick lookup
    for (int i = 0; i < n; i++)
    {
        nameToIndex[cities[i]->getCityName()] = i;
    }
    
    if (start == goal) // handle trivial case where start and goal are the same
    {
        path.clear();
        path.push_back(cities[nameToIndex[start]]);
        totalDistance = 0;
        return true;
    }

    auto itStart = nameToIndex.find(start);
    auto itGoal = nameToIndex.find(goal);

    if (itStart == nameToIndex.end() || itGoal == nameToIndex.end())
    {
        std::cerr << "Start or goal city not found!\n";
        return false;
    }

    // get the indices of start and goal cities
    int startIdx = itStart->second;
    int goalIdx = itGoal->second;

    std::vector<ld> g(n, std::numeric_limits<ld>::infinity()); // path cost from start to each city
    std::vector<int> cameFrom(n, -1); // save the backtracking path for path reconstruction

    // priority queue (open list) for nodes to explore, ordered by fCost
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
    std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>>
        openList([](std::shared_ptr<Node> a, std::shared_ptr<Node> b)
            { return a->fCost > b->fCost; });

    // initialize start node and push to open list
    g[startIdx] = 0.0;
    auto startNode = std::make_shared<Node>();
    startNode->cityName = start;
    startNode->gCost = 0.0;
    startNode->fCost = heuristic(*cities[startIdx], *cities[goalIdx]);
    openList.push(startNode);

    while (!openList.empty()) // main loop
    {
        auto current = openList.top();
        openList.pop();

        int u = nameToIndex[current->cityName];
        if (u == goalIdx) // goal reached, reconstruct path and calculate total cost
        {
            cost = g[goalIdx];
            path.clear();
            int curr = goalIdx;
            totalDistance = 0.0;

            while (curr != -1) // reconstruct path from cameFrom and calculate total distance
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

            if (!canDestroy(myBird, totalDistance)) // check if bird can cover total distance
                return false;
            
            return true;
        }

        for (int v = 0; v < n; v++) // explore neighbors
        {
            if (v == u) continue;

            ld dist = heuristic(*cities[u], *cities[v]); 

            if (!canBirdReach(myBird, dist)) // skip targets unreachable by the bird 
                continue;
            
            // calculate penalties for spies and enemy defenses
            ld spyPenalty = cities[v]->getIsSpy() ? myBird.getOutOfControl() : 0.0;
            int defenseLvl = 0;
            
            if (cities[v]->getStatus() == E)
            {
                auto theEnemy = std::dynamic_pointer_cast<Enemy>(cities[v]);
                defenseLvl = theEnemy->getDefenseLevel();
            }
            ld defensePenalty = std::pow(defenseLvl * 10, 2);

            ld tempG = g[u] + dist + spyPenalty + defensePenalty; // cost of reaching neighbor v
            if (tempG < g[v]) // update gCost, cameFrom, and push neighbor to open list if better path is found
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

    return false; // return false if the goal cannot be reached
}
bool Controler::canBirdReach(Bird & bird, ld distance)
{
    return bird.getOutOfControl() > distance;
}
bool Controler::canDestroy(Bird & bird, ld distance)
{
    if (bird.getDistance() >= 10000) // for Titan
    {
        return true;
    }
    
    return bird.getDistance() >= distance;
}
bool Controler::isDetected(Bird & bird)
{
    int numberOfSpy = countSpiesOnPath(bird.getThePath());

    if (numberOfSpy >= bird.getDegree())
    {
        return true;
    }

    return false;
}
void Controler::readCities()
{
    std::ifstream input("../src/Cities.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Cities file ! \n";

    ll count; // number of cities
    ld x, y;
    std::string name, situation;
    bool spy;
    
    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; ++i)
        {
            input >> name >> x >> y >> situation >> spy;

            // creating an object of the appropriate type :
            if (situation == "Normal")
            {
                auto city = std::make_shared<City>(name, x, y, spy);
                city->setStatus(N);

                cities.push_back(city);
            }
            else if (situation == "Enemy")
            {
                int level;
                input >> level;
                
                auto city = std::make_shared<Enemy>(name, x, y, spy, level);
                city->setStatus(E);

                cities.push_back(city);
                goalCities.push_back(city);
            }
            else if (situation == "Home")
            {
                int capacity;
                input >> capacity;

                auto city = std::make_shared<Home>(name, x, y, spy, capacity);
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
void Controler::shootDownBird(std::string enemyName) 
{
    std::unordered_map<std::string, std::shared_ptr<Enemy>> enemyMap;
    for (auto &city : goalCities)
    {
        auto enemyPtr = std::dynamic_pointer_cast<Enemy>(city);
        if (enemyPtr)
            enemyMap[city->getCityName()] = enemyPtr;
    }

    auto itEnemy = enemyMap.find(enemyName);
    if (itEnemy == enemyMap.end())
    {
        std::cerr << "Enemy " << enemyName << " not found!\n";
        return;
    }

    std::shared_ptr<Enemy> enemy = itEnemy->second;
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
    
    int range = std::min((int)detectedBirds.size(), enemy->getDefenseLevel());
    for (int i = 0; i < range ; i++)
    {
        std::cout << detectedBirds[i].getName() << " is destroyed by the enemies in [" << enemyName << "] \n";
        delBird(detectedBirds[i]);
    }
}
void Controler::newSpies(int targetNight)
{ 
    std::unordered_map<std::string , std::shared_ptr<City>> nameToCity; // for quick access
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
        int night; // night number
        iss >> night;

        if (night != targetNight) continue;

        std::string cityName;
        while(iss >> cityName)
        {
            nameToCity[cityName]->setIsSpy(true); // mark city as newly infiltrated by spies
        }
    }
}
void Controler::setReachBird(std::string enemyName, Bird &bird, std::vector<std::shared_ptr<City>> & path)
{
    std::unordered_map<std::string, std::shared_ptr<Enemy>> enemyMap;
    for (auto & city : goalCities)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(city);
        if (enemy)
            enemyMap[enemy->getCityName()] = enemy;
    }

    auto it = enemyMap.find(enemyName);
    if (it != enemyMap.end())
    {
        it->second->pushReachBird(bird);
        it->second->setBirdPath(path);
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
void Controler::deadBird(Bird & myBird , ld & totalDistance)
{
    auto it = std::find(birds.begin(), birds.end(), myBird);
    if (it != birds.end())
    {
        birds.erase(it);
        std::cout << "\nTOTAL DISTANCE: " << totalDistance << " | RANGE: " << myBird.getDistance() << "\n";
        std::cout << myBird.getName() << " is dead in the path! \n" ;  
    }
}
int Controler::countSpiesOnPath(std::vector<std::shared_ptr<City>> path)
{
    return std::count_if(path.begin(), path.end(), [](const std::shared_ptr<City> &city)
    {
        return city->getIsSpy();
    });
}
std::vector<Bird> & Controler::getBirds()
{
    return birds;
}
std::vector<std::shared_ptr<City>> Controler::getEnemies()
{
    return goalCities;
}
std::shared_ptr<Enemy> Controler::getWeakEnemy()
{
    std::shared_ptr<Enemy> weakest = nullptr;
    for (auto & city : goalCities)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(city);
        if (!enemy) continue;

        if (!weakest || enemy->getDefenseLevel() < weakest->getDefenseLevel())
        {
            weakest = enemy;
        }
    }

    return weakest;
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
    {
        std::cout << "WRONG NUMBER!";
    }

    scenario->readInputs(birds, startCities);
    return scenario;
}
std::pair<std::string, bool> Controler::findBestPairFor(std::shared_ptr<City> & start , Bird & bird, std::vector<std::shared_ptr<City>> & path, ld & distance)
{
    int minSpies = INT_MAX;
    ld minCost = LDBL_MAX;
    std::shared_ptr<City> bestGoal = nullptr;
    std::vector<std::shared_ptr<City>> bestPath;
    ll bestDis;
    bool flag;

    for (auto & goal : goalCities) 
    {
        ld cost;
        flag = aStar(start->getCityName(), goal->getCityName(), bird, path, distance, cost); 
        if (path.empty()) continue;
        
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

    // after processing all paths, update the optimal path and its distance
    path = bestPath;
    distance = bestDis;

    if (bestGoal == nullptr)
        return {"", false};

    return {bestGoal->getCityName(), flag};
}
