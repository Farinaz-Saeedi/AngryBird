#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler(){ std::cout << "inclontrol\n";}

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

            std::cout << str << '\n';

            if (situation == "Normal")
            {
                auto city = std::make_shared<City>(str, x, y, spy);
                city->setStatus(N);
                cities.push_back(city);
            }
            else if (situation == "Enemy")
            {
                auto city = std::make_shared<Enemy>(str, x, y, spy);
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
    else std::cout << "WRONG NUMBER!";
    scenario->readInputs(birds, homes);
    return scenario;
}
void Controler::run()
{
    readCities();
    findBestPairs();
    
    std::ifstream input("../src/Scenario.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scenario file ! \n";
        
    int numberOfScen;
    input >> numberOfScen;
    std::shared_ptr<Scenario> whichScen = readScenario(numberOfScen);
    std::cout << numberOfScen;
    whichScen->printOutput(*this);
}
void Controler::findBestPairs()
{
    bestPairs.clear();

    for (const auto &start : startCities)
    {
        ld bestEstimate = std::numeric_limits<double>::infinity();
        std::string bestGoalName = "";

        for (const auto &goal : goalCities)
        {
            ld estimate = heuristic(*start, *goal);
            if (estimate < bestEstimate)
            {
                bestEstimate = estimate;
                bestGoalName = goal->getCityName();
            }
        }

        if (!bestGoalName.empty())
        {
            bestPairs.push_back({start->getCityName(), bestGoalName});
            // push the bird to goal city
        }
    }

    std::cout << "Best Pairs (" << bestPairs.size() << "):\n";
    for (const auto &x : bestPairs)
    {
        std::cout << x.first << " -> " << x.second << '\n';
    }
}

ld Controler::heuristic(City &a, City &b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}
void Controler::aStar(std::string start, std::string goal, Bird myBird)
{
    ll n = cities.size();
    
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
    std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>>openList
    (
        [](std::shared_ptr<Node> a, std::shared_ptr<Node> b)
        { return a->fCost > b->fCost; }
    );
    
    g[startIdx] = 0.0;
    auto startNode = std::make_shared<Node>();
    startNode->cityNamee = start;
    startNode->gCost = 0.0;
    startNode->fCost = heuristic(*cities[startIdx], *cities[goalIdx]);
    
    openList.push(startNode);
    
    while (!openList.empty())
    {
        auto current = openList.top();
        openList.pop();

        int u = nameToIndex[current->cityNamee];
        if (u == goalIdx)
        {
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
                neighborNode->cityNamee = cities[v]->getCityName();
                neighborNode->gCost = tempG;
                neighborNode->fCost = tempG + heuristic(*cities[v], *cities[goalIdx]);

                openList.push(neighborNode);
            }
        }
    }

    int curr = goalIdx;
    if (cameFrom[curr] == -1)
    {
        return;
    }

    ld totalDistance = 0.0;

    while (curr != -1)
    {
        path.push_back(cities[curr]);

        int prev = cameFrom[curr];
        if ( prev != -1 )
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
}
bool Controler::canBirdReach(Bird & bird , ld distance)
{
    return bird.getOutOfControl() > distance;
}
bool Controler::canDestroy(Bird & bird , ld distance)
{
    return bird.getDistance() >= distance;
}
bool Controler::isDetected(Bird & bird)
{
    ll numberOfSpy = 0;
    for(auto &it : path)
    {
        if (it->getIsSpy())
        {
            numberOfSpy++;
        } 
    }

    if (numberOfSpy >= bird.getDegree())
    {
        return true;
    }
    return false; 
}
void Controler::shootDownBird(Enemy &enemy) // call after A*
{
    std::vector<Bird> detectedBirds;

    for (auto &it : enemy.getReachBirds())
    {
        if (isDetected(it))
        {
            detectedBirds.push_back(it);
        }
    }

   
    std::sort(detectedBirds.begin(), detectedBirds.end(), [](Bird &a, Bird &b)
    {
        return a.getDemolition() > b.getDemolition();
    });


    for (int i = 0; i < enemy.getDefenseLevel() && i < detectedBirds.size(); i++)
    {
        for (auto it = birds.begin(); it != birds.end(); it++)
        {
            if (it->getName() == detectedBirds[i].getName())
            {
                birds.erase(it);
                break;
            }
        }
    }
}
std::pair<std::string , std::string> Controler::getTopBestPair()
{
    std::pair<std::string , std::string> top = bestPairs[bestPairs.size()-1];
    bestPairs.pop_back();
    return top;
}
ld Controler::totoalDamage(std::vector<std::string> &path, Bird & bird)
{
    ld damage = 0.0;

    std::unordered_set<std::string> enemyCityNames;
    for (auto &goalCity : goalCities)
    {
        enemyCityNames.insert(goalCity->getCityName());
    }

    for (auto &cityName : path)
    {
        if (enemyCityNames.count(cityName))
        {
            damage += bird.getDemolition();
        }
    }
    return damage;
}
std::vector<std::shared_ptr<City>> Controler::getPath()
{
    return path;
}
