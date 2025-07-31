#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler() {}

ll Controler::getNumberOfCities()
{
    return numberOfCities;
}
std::vector<Bird> Controler::getBirds()
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
    std::cout << "scen" << whichScen << '\n';
    whichScen->printOutput(*this , startCities);
}
std::string Controler::findBestPairFor(std::shared_ptr<City> & start , Bird & bird)
{
    int minSpies = INT_MAX;
    std::shared_ptr<City> bestGoal = nullptr;

    for (auto & goal : goalCities) {
        auto path = aStar(start->getCityName(), goal->getCityName(), bird); 
        int spies = countSpiesOnPath(path);

        if (spies < minSpies) { 
            minSpies = spies;
            bestGoal = goal;
        }
    }

    return bestGoal->getCityName();
}
ld Controler::heuristic(City &a, City &b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}
std::vector<std::shared_ptr<City>> Controler::aStar(std::string start, std::string goal, Bird myBird)
{
    ll n = cities.size();
    std::vector<std::shared_ptr<City>> path;

    std::unordered_map<std::string, int> nameToIndex;
    for (int i = 0; i < n; i++)
    {
        nameToIndex[cities[i]->getCityName()] = i;
    }

    int startIdx = nameToIndex[start];
    int goalIdx = nameToIndex[goal];

    std::vector<ld> g(n, std::numeric_limits<ld>::infinity());
    std::vector<int> cameFrom(n, -1);

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
    std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>>
        openList( [](std::shared_ptr<Node> a, std::shared_ptr<Node> b)
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
            cameFrom[goalIdx] = cameFrom[u]; 
            break;
        }

        for (int v = 0; v < n; ++v)
        {
            if (v == u)
                continue;

            ld dist = heuristic(*cities[u], *cities[v]);
            if (!canBirdReach(myBird, dist))
                continue;

            ld penalty = cities[v]->getIsSpy() ? myBird.getOutOfControl() : 0.0;
            ld tempG = g[u] + dist + penalty;

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

    int curr = goalIdx;
    if (cameFrom[curr] == -1)
    {
        return{};
    }

    ld totalDistance = 0.0;

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
    {
        auto it = std::find(birds.begin(), birds.end(), myBird);
        if (it != birds.end())
        {
            birds.erase(it);
        }
    }
    return path;
}
bool Controler::canBirdReach(Bird &bird, ld distance)
{
    return bird.getOutOfControl() > distance;
}
bool Controler::canDestroy(Bird &bird, ld distance)
{
    return bird.getDistance() >= distance;
}
bool Controler::isDetected(Bird &bird)
{
    std::cout << "*********fun\n\n";
    int numberOfSpy = countSpiesOnPath(chosenPath);

    std::cout << "number of spy: " << numberOfSpy << '\n';

    if (numberOfSpy >= bird.getDegree())
    {
        return true;
    }
    return false;
}
void Controler::shootDownBird(std::string enemyName) // call after A*
{
    std::shared_ptr<Enemy> enemy;
    for (int i = 0; i < goalCities.size(); i++)
    {
        if (goalCities[i]->getCityName() == enemyName)
            enemy = std::dynamic_pointer_cast<Enemy>(goalCities[i]);
    }

    std::vector<Bird> detectedBirds;
    
    for (auto &it : enemy->getReachBirds())
    {
        if (isDetected(it))
        {
            std::cout << "meowwwww*_*\n";
            detectedBirds.push_back(it);
        }
    }
    
    std::sort(detectedBirds.begin(), detectedBirds.end(), [](Bird &a, Bird &b)
    { return a.getDemolition() > b.getDemolition(); });
    
    std::unordered_map<std::string, std::vector<Bird>::iterator> birdMap;
    
    for (auto it = detectedBirds.begin(); it != detectedBirds.end(); it++)
    {
        birdMap[it->getName()] = it;
    }

    std::cout <<"birds " << detectedBirds.size() << " level " << enemy->getDefenseLevel() << '\n';
    
    int range = std::min((int)detectedBirds.size(), enemy->getDefenseLevel());
    std::cout << range << " : range\n";
    for (int i = 0; i < range && enemy->getIsReady(); i++)
    {
        std::cout << detectedBirds[i].getName() << " is del *** \n";
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
int Controler::countSpiesOnPath(std::vector<std::shared_ptr<City>> & path)
{
    int numberOfspies = 0;
    for ( auto city : path )
    {
        if (city->getIsSpy())
            numberOfspies++;
    }
    return numberOfspies;
}
void Controler::newSpies()
{
    ll spyCount;
    std::cout << "\nHow many new spy cities? ";
    std::cin >> spyCount;

    std::unordered_map<std::string, std::shared_ptr<City>> cityMap;
    for (auto& city : cities)
    {
        cityMap[city->getCityName()] = city;
    }

    std::cout << "\nEnter city names with new spies:\n";
    for (int i = 0; i < spyCount; i++)
    {
        std::string cityName;
        std::cin >> cityName;

        auto it = cityMap.find(cityName);
        if (it != cityMap.end())
        {
            it->second->setIsSpy(true);
        }
    }
}
void Controler::enemyReady()
{
    for(auto &enemy : goalCities)
    {
        auto temp = std::dynamic_pointer_cast<Enemy>(enemy);
        temp->setIsReady(true);   
    }   
}
void Controler::setReachBird(std::string &enemyName, Bird &bird)
{
    std::shared_ptr<Enemy> enemy ;
    for (int i = 0; i < goalCities.size(); i++)
    {
        if (goalCities[i]->getCityName() == enemyName)
            enemy = std::dynamic_pointer_cast<Enemy>(goalCities[i]);
    }
    enemy->pushReachBird(bird);
}
void Controler::attack()
{
    for (auto & goal : goalCities)
    {
        shootDownBird(goal->getCityName());
    }
}
void Controler::delBird(Bird & bird)
{
    auto it = std::find(birds.begin(), birds.end(), bird);
    if (it != birds.end()) {
        birds.erase(it);
    }
}