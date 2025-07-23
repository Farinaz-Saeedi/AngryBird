#include <bits/stdc++.h>

#include "Controler.hpp"

#define ll long long

Controler::Controler(){}
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
void Controler::readCities()
{
    std::ifstream input("Cities.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Cities file ! \n";

    ll count;
    ld x, y;
    std::string str, situation;
    bool spy;

    while (!input.eof())
    {
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> str >> x >> y >> situation >> spy;

            if (situation == "Normal")
            {
                auto city = std::make_unique<City>(str, x, y, spy);
                city->setStatus(N);
                cities.push_back(std::move(city));
            }
            else if (situation == "Enemy")
            {
                auto city = std::make_unique<Enemy>(str, x, y, spy);
                city->setStatus(E);
                cities.push_back(std::move(city));
                goalCities.push_back(std::move(city));
            }
            else if (situation == "Home")
            {
                int capacity;
                input >> capacity;

                auto city = std::make_unique<Home>(str, x, y, spy, capacity);
                city->setStatus(H);
                cities.push_back(std::move(city));
                startCities.push_back(std::move(city));
            }
        }
    }
    input.close();
}
void Controler::setNumberOfCities(ll numberOfCities)
{
    this->numberOfCities = numberOfCities;
}
void Controler::readScenario(int scen)
{
    if (scen == 1)
    {
        Scenario1 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 2)
    {
        Scenario2 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 3)
    {
        Scenario3 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 4)
    {
        Scenario4 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 5)
    {
        Scenario5 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 6)
    {
        Scenario6 scenario;
        scenario.readInputs(birds, homes);
    }
    else if (scen == 7)
    {
        Scenario7 scenario;
        scenario.readInputs(birds, homes);
    }
    else std::cout << "WRONG NUMBER!";
}
void Controler::run()
{
    int numberOfScen;

    std::ifstream input("../src/Scenario.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scenario file ! \n";

    input >> numberOfScen;
    readScenario(numberOfScen);
   // printBirds();
}
// void Controler::printBirds() // testing
// {
//     std::cout << birds.size() << '\n';
//     for ( auto & bird : birds )
//         std::cout << bird.getName() << " \n" ;
// }
std::pair<std::string, std::string> Controler::findBestPair()
{
    ld bestEstimate = std::numeric_limits<double>::infinity();
    std::pair<std::string, std::string> bestPair = {NULL, NULL};

    for (const auto &start : startCities)
    {
        for (const auto &goal : goalCities)
        {
            ld estimate = heuristic(*start, *goal);
            if (estimate < bestEstimate)
            {
                bestEstimate = estimate;
                bestPair = {start->getCityName(), goal->getCityName()};
            }
        }
    }

    return bestPair;
}
ld Controler::heuristic(City &a, City &b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}
std::vector<std::string> Controler::aStar(std::string start, std::string goal, ld maxDistance)
{
    ll n = cities.size();

    std::unordered_map<std::string, int> nameToIndex;
    for (int i = 0; i < n; i++)
    {
        nameToIndex[cities[i]->getCityName()] = i;
    }

    int startIdx = nameToIndex[start];
    int goalIdx = nameToIndex[goal];

    ld totalDistance = calDistance(*cities[startIdx], *cities[goalIdx]);

    std::vector<ld> g(n, std::numeric_limits<ld>::infinity());
    std::vector<int> cameFrom(n, -1);

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
    std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>>openList
    (
        [](std::shared_ptr<Node> a, std::shared_ptr<Node> b)
        { return a->fCost > b->gCost; }
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
            {
                continue;
            }

            ld dist = heuristic(*cities[u], *cities[v]);
          
            
            if (dist > maxDistance)
            {
                continue;
            }

            double tentative_g = g[u] + dist;
            if (tentative_g < g[v])
            {
                g[v] = tentative_g;
                cameFrom[v] = u;

                auto neighborNode = std::make_shared<Node>();
                neighborNode->cityNamee = cities[v]->getCityName();
                neighborNode->gCost = tentative_g;
                neighborNode->fCost = tentative_g + heuristic(*cities[v], *cities[goalIdx]);

                openList.push(neighborNode);
            }
        }
    }

    std::vector<std::string> path;
    int curr = goalIdx;
    if (cameFrom[curr] == -1)
    {
        return {};
    }

    while (curr != -1)
    {
        path.push_back(cities[curr]->getCityName());
        curr = cameFrom[curr];
    }

    reverse(path.begin(), path.end());
    return path;
}
bool Controler::canBirdReach(Bird & bird , ld distance)
{
    return bird.getOutOfControl() >= distance;
}
bool Controler::canDestroy(Bird & bird , ld distance)
{
    return bird.getDistance() >= distance;
}
