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
        //std::cout << "while";

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
    //std::cout << "end read********";
    input.close();
}
// void Scenario5::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
// {
//     for (int i = 0; i < getNumberOfNights(); i++)
//     {
//         std::cout << "\nNight " << i + 1 << " begins...\n";
//         ld totalDamage = 0.0;
//         for (auto &home : homes)
//         {
//             auto myHome = std::dynamic_pointer_cast<Home>(home);
//             if (!myHome)
//                 continue;
//             auto &birds = myHome->getMyBirds();
//             if (birds.empty())
//                 continue;
//             for (auto &bird : birds)
//             {
//                 ll distance = 0;
//                 std::vector<std::shared_ptr<City>> path;
//                 auto [enemy, canDestroy] = control.findBestPairFor(home, bird, path, distance);
//                 std::cout << "Bird : " << bird.getName() << "\nPath: ";
//                 if (canDestroy != 1)
//                     control.deadBird(bird, distance);
//                 else
//                 {
//                     control.setReachBird(enemy, bird, path);
//                     for (auto &city : path)
//                     {
//                         std::cout << city->getCityName() << " ";
//                     }
//                 }
//                 std::cout << "\n---------------------------------------\n";
//                 std::cout << "\n";
//             }
//         }
//         std::cout << "\n---------------------------------------\n";
//         control.attack();
//         auto birds = control.getBirds();
//         for (auto &bird : birds)
//         {
//             totalDamage += bird.getDemolition();
//         }
//         std::cout << "---------------------------------------";
//         std::cout << "\nTotal Damage (Neight " << i << " ): " << totalDamage << "\n";
//         std::cout << "---------------------------------------\n";
//         control.newSpies();
//     }
// }
std::vector<int> Scenario5::hungarianMaximize(const std::vector<std::vector<ll>> &profit)
{
    int n = (int)profit.size();
    int m = (int)profit[0].size();

    ll maxProfit = std::numeric_limits<ll>::min();
    for (const auto &row : profit)
    {
        for (auto val : row)
        {
            if (val > maxProfit)
            {
                maxProfit = val;
            }
        }
    }

    std::vector<std::vector<ll>> cost(n, std::vector<ll>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cost[i][j] = maxProfit - profit[i][j];
        }
    }

    std::vector<ll> u(n + 1), v(m + 1);
    std::vector<int> p(m + 1), way(m + 1);

    for (int i = 1; i <= n; i++)
    {
        p[0] = i;
        int j0 = 0;
        std::vector<ll> minv(m + 1, std::numeric_limits<ll>::max());
        std::vector<bool> used(m + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = std::numeric_limits<ll>::max();
            for (int j = 1; j <= m; j++)
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
            for (int j = 0; j <= m; j++)
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

    std::vector<int> ans(n, -1);
    for (int j = 1; j <= m; j++)
    {
        if (p[j] != 0 && p[j] - 1 < n && j - 1 < m)
        {
            ans[p[j] - 1] = j - 1;
        }
    }
    return ans;
}
double Scenario5::getSpyDetectionProbability(int night)
{

    double baseProb = 0.1;
    double prob = baseProb * night;

    if (prob > 1.0)
        prob = 1.0;

    return prob;
}

void Scenario5::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ll totalDamage = 0;

    for (int night = 1; night <= numberOfNights; ++night)
    {
        std::cout << "\nNight " << night << " begins...\n\n";

        double detectionProb = getSpyDetectionProbability(night);

        for (auto &home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (!myHome)
                continue;

            if (myHome->getCapacity() <= 0)
                continue;

            auto &birds = myHome->getMyBirds();
            if (birds.empty())
                continue;

            for (auto &bird:birds)
            {
              
                if (bird.getDemolition() <= 0)
                    continue;

                for (auto &target : control.getEnemies())
                {
                    ll distance;
                    ld cost;
                    control.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance, cost);

                    if (!path.empty())
                    {
                        ll dmg = bird.getDemolition();
                        options.push_back({bird, home, target, path, cost, dmg, 1.0 - detectionProb});
                    }
                }
            }
        }

        if (options.empty())
        {
            std::cout << "No launches possible this night.\n";
            control.newSpies();

            continue;
        }

        int n = options.size();
        std::vector<std::vector<long long>> profit(n, std::vector<ll>(n, LLONG_MIN));
        for (int i = 0; i < n; ++i)
        {
            profit[i][i] = static_cast<long long>(options[i].damage * options[i].successProb * 1e6);
        }

        std::vector<int> match = hungarianMaximize(profit);

        for (int i = 0; i < n; ++i)
        {
            int j = match[i];
            if (j == -1)
                continue;

            auto &opt = options[i];
            std::cout << "\nLaunch Bird " << opt.bird.getName()
                      << " from " << opt.home->getCityName()
                      << " to " << opt.target->getCityName()
                      << " | Expected Damage: " << (opt.damage * opt.successProb) << "\n\n";

            std::cout << "Path: ";
            for (auto &city : opt.path)
            {
                std::cout << city->getCityName() << " ";
            }
            std::cout << "\n";

            totalDamage += opt.damage;

            for (auto &home : homes)
            {
                if (home->getCityName() == opt.home->getCityName())
                {
                    auto myHome = std::dynamic_pointer_cast<Home>(home);
                    if (!myHome)
                        continue;
                    auto &birds = myHome->getMyBirds();

                    birds.erase(remove_if(birds.begin(), birds.end(),
                                          [&](Bird &b)
                                          { return &b == &opt.bird; }),
                                birds.end());

                    myHome->reduceCapacity();
                    break;
                }
            }
        }

        control.newSpies();
    }

    std::cout << "=== Total Damage: " << totalDamage << " ===\n";
}