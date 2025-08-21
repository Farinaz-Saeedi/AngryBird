#include "Scenario3.hpp"

void Scenario3::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario3.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-3 file ! \n";

    ll count, numberOfBird;
    std::string name;

    while (input >> count)
    {
        for (int i = 0; i < count; i++)
        {
            input >> name >> numberOfBird;
            for (int j = 0; j < numberOfBird; j++) // create each bird in the group
            {
                readBird(name, birds);
            }
        }
    }

    input.close();
}
void Scenario3::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    ll totalDamage = 0;

    assignOptions(control, homes); // generate all possible bird-target options
    auto profitMatrix = buildProfitMatrix(control); // create profit matrix for Hungarian algorithm
    auto matches = hungarianMin(profitMatrix); // find optimal assignment of birds to targets
    auto birds = control.getBirds();

    for (int i = 0; i < matches.size(); i++)
    {
        int idx = matches[i];
        if (idx == -1 || idx >= options.size())
            continue;

        const auto &opt = options[idx]; // get assigned option for this bird

        std::cout << "Bird: " << birds[opt.birdIdx].getName() << " | " << "Home: " << opt.home->getCityName() << " | ";
        std::cout << "Target: " << opt.target->getCityName() << '\n';
        std::cout << "Path: ";

        auto path = opt.path;
        for (auto city : path)
            std::cout << city->getCityName() << " ";

        std::cout << "\n---------------------------------------\n";
    }

    control.attack(); // execute attacks based on assignments

    birds = control.getBirds();
    for (auto &bird : birds)
    {
        totalDamage += bird.getDemolition();
    }

    std::cout << "\n---------------------------------------\n";
    std::cout << "Total Damage: " << totalDamage << "\n";
    std::cout << "---------------------------------------\n";
}
std::vector<OptionScen3> Scenario3::assignOptions(Controler & control, std::vector<std::shared_ptr<City>> & homes)
{
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> path;
    ld distance;

    std::sort(birds.begin(), birds.end(), [](Bird & a, Bird & b) 
              { return a.getDemolition() > b.getDemolition(); });

    for (int b = 0; b < birds.size(); b++)
    {
        Bird bird = birds[b];

        for (auto & home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home); // cast City pointer to Home pointer
            if (myHome->getCapacity() <= 0) // skip home if it has no available capacity
                continue;

            for (auto & target : control.getEnemies())
            {
                ld cost;
                control.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance, cost);

                if (!path.empty() && !control.isDetected(bird))
                {
                    ll dmg = bird.getDemolition();
                    options.push_back({b, home, target, path, cost}); // store this option in the options vector
                    myHome->reduceCapacity(); // reduce home capacity after assigning a bird
                }
            }
        }
    }

    return options;
}
std::vector<int> Scenario3::hungarianMin(const std::vector<std::vector<ll>> & profitMatrix)
{
    const ll INF = std::numeric_limits<ll>::max();

    int n = profitMatrix.size();    // number of rows
    int m = profitMatrix[0].size(); // number of columns
    int size = std::max(n, m);      // square matrix size

    std::vector<std::vector<ll>> cost(size, std::vector<ll>(size, INF)); // create a square matrix of profits
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cost[i][j] = profitMatrix[i][j];


    std::vector<ll> u(size + 1), v(size + 1); // dual variables
    std::vector<int> p(size + 1); // the row assigned to column j in the current path
    std::vector<int> way(size + 1); // to reconstruct the minimum path 


    for (int i = 1; i <= size; i++) // finding the optimal path to the target for each bird
    {
        p[0] = i; // current row
        int j0 = 0;
        std::vector<ll> minv(size + 1, INF); // minimal values for augmenting path
        std::vector<bool> used(size + 1, false); // used columns
        do // finding an augmenting path
        {
            used[j0] = true; // reviewed
            int i0 = p[j0], j1 = 0;
            ll delta = INF;

            for (int j = 1; j <= size; j++) // find minimal slack
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
            for (int j = 0; j <= size; j++) // update dual variables
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

        do // reconstructing the augmenting path
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    std::vector<int> result(n, -1); // final assignment
    for (int j = 1; j <= size; ++j)
        if (p[j] <= n && j <= m)
            result[p[j] - 1] = j - 1;

    return result; // return assignment of rows to columns
}
std::vector<std::vector<ll>> Scenario3::buildProfitMatrix(Controler & control)
{
    int n = control.getBirds().size();
    int m = options.size();

    std::vector<std::vector<ll>> profit(n, std::vector<ll>(m, 1e9));

    for (int i = 0; i < m; i++) // iterate over each target option
    {
        const auto &option = options[i];
        profit[option.birdIdx][i] = option.cost; // set the cost for assigning this bird to this target
    }

    return profit;
}
