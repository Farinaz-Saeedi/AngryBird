#include "Scenario3.hpp"

void Scenario3::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario3.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-3 file ! \n";

    ll count, number;
    std::string name;

    while (input >> count)
    {
        for (int i = 0; i < count; ++i)
        {
            input >> name >> number;
            for (int j = 0; j < number; ++j)
            {
                readBird(name, birds);
                std::cout << name << '\n';
            }
        }
    }

    input.close();
}
void Scenario3::setSlingshot(int number)
{
    numberOfSlingshot = number;
}
int Scenario3::getSlingshot()
{
    return numberOfSlingshot;
}
void Scenario3::printOutput(Controler & control , std::vector<std::shared_ptr<City>> &homes)
{
    int count = 0;
    ll totalDamage = 0;
    assignOptions(control, homes);
    auto profitMatrix = buildProfitMatrix(control);
    auto matches = hungarianMin(profitMatrix);
    auto birds = control.getBirds();

    for (int i = 0; i < matches.size(); ++i)
    {
        int idx = matches[i];
        if (idx == -1 || idx >= options.size())
            continue;

        const auto &opt = options[idx];
        std::cout << "Bird: " << birds[opt.birdIdx].getName() << " | " << "Home: " << opt.home->getCityName() << " | ";
        std::cout << "Target: " << opt.target->getCityName() << '\n';
        std::cout << "Path: ";
        auto path = opt.path;
        for (auto city : path)
            std::cout << city->getCityName() << " ";
        std::cout << "\n---------------------------------------\n";

        // auto myHome = std::dynamic_pointer_cast<Home>(opt.home);
        // myHome->reduceCapacity();
    }

    control.attack();

    birds = control.getBirds();
    for (auto &bird : birds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "\n---------------------------------------";
    std::cout << "\nTotal Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
std::vector<OptionScen3> Scenario3::assignOptions(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> path;
    ld distance;

    std::sort(birds.begin(), birds.end(), [](Bird &a, Bird &b)
              { return a.getDemolition() > b.getDemolition(); });

    for (int b = 0; b < birds.size(); ++b)
    {
        Bird bird = birds[b];

        for (auto &home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (myHome->getCapacity() <= 0)
                continue;

            for (auto &target : control.getEnemies())
            {
                ld cost;
                control.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance, cost);

                if (!path.empty() && !control.isDetected(bird))
                {
                    ll dmg = bird.getDemolition();
                    options.push_back({b, home, target, path, cost});
                    myHome->reduceCapacity();
                }
            }
        }
    }

    return options;
}
std::vector<int> Scenario3::hungarianMin(const std::vector<std::vector<ll>> &profitMatrix)
{
    const ll INF = std::numeric_limits<ll>::max();
    ;

    int n = profitMatrix.size();
    int m = profitMatrix[0].size();
    int size = std::max(n, m);

    std::vector<std::vector<ll>> cost(size, std::vector<ll>(size, INF));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cost[i][j] = profitMatrix[i][j];

    std::vector<ll> u(size + 1), v(size + 1);
    std::vector<int> p(size + 1), way(size + 1);

    for (int i = 1; i <= size; ++i)
    {
        p[0] = i;
        int j0 = 0;
        std::vector<ll> minv(size + 1, INF);
        std::vector<bool> used(size + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= size; ++j)
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
            for (int j = 0; j <= size; ++j)
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
    for (int j = 1; j <= size; ++j)
        if (p[j] <= n && j <= m)
            result[p[j] - 1] = j - 1;

    return result;
}
std::vector<std::vector<ll>> Scenario3::buildProfitMatrix(Controler &control)
{
    int n = control.getBirds().size();
    int m = options.size();

    std::vector<std::vector<ll>> profit(n, std::vector<ll>(m, 1e9));

    for (int j = 0; j < m; ++j)
    {
        const auto &option = options[j];
        // std::cout << option.home->getCityName() << " -> " << option.target->getCityName() << " -- " << option.birdIdx << " cost : " << option.cost << '\n';
        profit[option.birdIdx][j] = option.cost;
    }

    return profit;
}
