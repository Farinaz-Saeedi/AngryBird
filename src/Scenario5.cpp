#include "Scenario5.hpp"

int Scenario5::getNumberOfNights()
{
    return numberOfNights;
}
void Scenario5::setNumberOfNights(int numberOfNights)
{
    this->numberOfNights = numberOfNights;
}
void Scenario5::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario5.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-5 file ! \n";

    int nights;
    ll count;
    std::string name;

    while (!input.eof())
    {
        input >> nights;
        setNumberOfNights(nights);

        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            Bird temp = readBird(name, birds);

            input >> name;
            birds[birds.size() - 1].setHomePlace(name);

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (home->getCityName() == name)
                {
                    home->push(temp);
                    break;
                }
            }
        }
    }
    input.close();
}
void Scenario5::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ll totalDamage = 0;
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> enemies = control.getEnemies();
    std::vector<Bird> aliveBirds;

    std::unordered_map<std::string, std::shared_ptr<City>> homeMap;
    for (auto &home : homes)
        homeMap[home->getCityName()] = home;

    std::unordered_map<std::string, std::shared_ptr<City>> enemyMap;
    for (auto &enemy : enemies)
        enemyMap[enemy->getCityName()] = enemy;

    for (int night = 1; night <= getNumberOfNights(); ++night)
    {
        std::cout << "\nNight " << night << " begins ...\n\n";

        control.newSpies(night);

        firstOptions.clear();
        allOptions.clear();
        firstOptions.reserve(birds.size());

        std::unordered_map<std::string, std::vector<OptionScen5>> enemyToSecondOptions;

        for (int b = 0; b < birds.size(); ++b)
        {

            auto itHome = homeMap.find(birds[b].getHomePlace());
            if (itHome == homeMap.end())
                continue;
            auto myHome = std::dynamic_pointer_cast<Home>(itHome->second);
            if (!myHome)
                continue;

            ll distance = 0.0;
            ld cost;
            std::vector<std::shared_ptr<City>> path;

            for (auto &target : control.getEnemies())
            {
                bool can = control.aStar(itHome->second->getCityName(), target->getCityName(), birds[b], path, distance, cost);
                if (path.empty() || !can)
                    continue;

                // std::cout << "--bird name: " << birds[b].getName() << '\n';
                
                OptionScen5 opt{b, birds[b].getDegree(), itHome->second, target, path, birds[b].getDemolition(), 0.0};
                birds[b].setThePath(path);
                allOptions.push_back(opt);
                if (control.isDetected(birds[b]))
                {
                    std::cout << birds[b].getName() << "----\n";
                    enemyToSecondOptions[target->getCityName()].push_back(opt);
                    continue;
                } else
                    firstOptions.push_back(opt);
                    std::cout << birds[opt.birdIdx].getName() << " Bird\n";
            }
        }

        std::sort(firstOptions.begin() , firstOptions.end() , [](OptionScen5 & a , OptionScen5 & b)
        {
            if ( a.spyNum != b.spyNum ) return a.spyNum > b.spyNum ;
            return a.damage < b.damage ;
        });

        std::unordered_set<int> usedBirds;
        usedBirds.clear();
        birdsToRemove.clear();

        if (!firstOptions.empty())
        {
            std::cout << "planA\n";
            auto opt = firstOptions.back();

            control.setReachBird(opt.target->getCityName(), birds[opt.birdIdx], opt.path);
            totalDamage += opt.damage;
            std::cout << "Bird " << birds[opt.birdIdx].getName() <<  " | " << opt.home->getCityName() << " -> " << opt.target->getCityName();
            std::cout << "\nPath: ";
            for (auto & city : opt.path)
                std::cout << city->getCityName() << " ";
            std::cout << "\n--------------------------------\n";
            birdsToRemove.push_back(opt.birdIdx);
        } 
        else 
        {
            std::shared_ptr<Enemy> weakEnemy = control.getWeakEnemy();
            int capacity = weakEnemy->getDefenseLevel();
            auto opts = enemyToSecondOptions[weakEnemy->getCityName()];

            std::sort(opts.begin() , opts.end() , [](auto &a , auto &b) 
            {
                return a.damage > b.damage;
            });

            for (int i = 0 ; i < capacity + 1 ; ++i)
            {
                if (usedBirds.count(opts[i].birdIdx)) continue;

                control.setReachBird(opts[i].target->getCityName(), birds[opts[i].birdIdx], opts[i].path);

                // totalDamage += opts[i].damage;
                std::cout << "Bird " << birds[opts[i].birdIdx].getName() << " | " << opts[i].home->getCityName()
                          << " -> " << opts[i].target->getCityName() << "\nPath: ";
                for (auto & city : opts[i].path)
                    std::cout << city->getCityName() << " ";
                std::cout << "\n--------------------------------\n";

                usedBirds.insert(opts[i].birdIdx);
                birdsToRemove.push_back(opts[i].birdIdx);
                // aliveBirds.push_back(birds[opts[i].birdIdx]);
            
                std::cout << "planB\n";
            }
        }
        
        if (night == getNumberOfNights())
        {
            for (auto & opt : allOptions)
            {
                if (usedBirds.count(opt.birdIdx)) continue;
                
                control.setReachBird(opt.target->getCityName(), birds[opt.birdIdx], opt.path);

                // totalDamage += opt.damage;
                std::cout << "Bird " << birds[opt.birdIdx].getName() << " | " << opt.home->getCityName()
                << " -> " << opt.target->getCityName() << "\nPath: ";
                for (auto & city : opt.path)
                std::cout << city->getCityName() << " ";
                std::cout << "\n--------------------------------\n";
                usedBirds.insert(opt.birdIdx);
                birdsToRemove.push_back(opt.birdIdx);
                // aliveBirds.push_back(birds[opt.birdIdx]);

                std::cout << "last\n";
            }
        }

        control.attack();

        std::sort(birdsToRemove.rbegin(), birdsToRemove.rend());
        for (int idx : birdsToRemove)
        {
            std::cout << "erase: " << idx << '\n';
            birds.erase(birds.begin() + idx);
        }

        std::cout << "-- Total Damage: " << totalDamage << " --\n";
    }
}
std::vector<int> Scenario5::hungarianMax(const std::vector<std::vector<ll>> &profit)
{
    int n = profit.size();
    if (n == 0)
        return {};
    int m = profit[0].size();
    if (m == 0)
        return {};

    ll maxVal = 0;
    for (auto &row : profit)
        for (auto val : row)
            maxVal = std::max(maxVal, val);

    std::vector<std::vector<ll>> cost(n, std::vector<ll>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cost[i][j] = maxVal - profit[i][j];

    if (n < m)
    {
        cost.resize(m, std::vector<ll>(m, maxVal));
        n = m;
    }
    else if (m < n)
    {
        for (auto &row : cost)
            row.resize(n, maxVal);
        m = n;
    }

    std::vector<ll> u(n + 1), v(m + 1), p(m + 1), way(m + 1);

    for (int i = 1; i <= n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        std::vector<ll> minv(m + 1, LLONG_MAX);
        std::vector<bool> used(m + 1, false);

        do
        {
            used[j0] = true;
            int i0 = p[j0];
            ll delta = LLONG_MAX;
            int j1 = 0;

            for (int j = 1; j <= m; ++j)
            {
                if (!used[j])
                {
                    ll cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                    {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta)
                    {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= m; ++j)
            {
                if (used[j])
                {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    std::vector<int> result(n, -1);
    for (int j = 1; j <= m; ++j)
        if (p[j] > 0)
            result[p[j] - 1] = j - 1;

    return result;
}