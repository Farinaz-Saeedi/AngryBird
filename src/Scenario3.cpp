#include "Scenario3.hpp"


void Scenario3::readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes)
{
    std::ifstream input("../src/Scenario3.txt");
    if (!input.is_open())
    std::cerr << " Unable to open Scen-3 file ! \n";
    
    ll count, number;
    std::string name;

    while (input >> count)
    {
        // input >> count;
        // setSlingshot(count);
        
        // input >> count;
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
    int count = 0 ;
    assignOptions(control, homes);
    auto profitMatrix = buildProfitMatrix(control);
    auto matches = hungarianMaximize(profitMatrix);
    auto birds = control.getBirds();

    for (int i = 0 ; i < matches.size() ; ++i)
    {
        int idx = matches[i];
        if (idx == -1) continue;
        const auto & opt = options[idx];
        std::cout << "Bird: " << birds[opt.birdIdx].getName() << " | " << "Home: " << opt.home->getCityName() << " | \n";
        std::cout << "Target: " << opt.target->getCityName() << '\n';
        std::cout << "Path: \n";
        auto path = opt.path;
        for ( auto city : path )
            std::cout << city->getCityName() << " ";
        std::cout << "\n-----------------------------\n";

        auto myHome = std::dynamic_pointer_cast<Home>(opt.home);
        myHome->reduceCapacity();
    }

}
std::vector<AssignmentOption> Scenario3::assignOptions(Controler & control , std::vector<std::shared_ptr<City>> & homes) 
{
    std::vector<Bird> birds = control.getBirds();
    std::vector<std::shared_ptr<City>> path;
    ll distance;

    for (int b = 0 ; b < birds.size() ; ++b) 
    {
        Bird bird = birds[b];

        for (auto & home : homes) 
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (myHome->getCapacity() == 0) continue;

            for (auto & target : control.getEnemies()) 
            {
                control.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance);

                if (!path.empty() && !control.isDetected(bird))
                {
                    ll dmg = bird.getDemolition();  
                    options.push_back({b, home, target, path, dmg});
                }
            }
        }
    }

    return options;
}
std::vector<int> Scenario3::hungarianMaximize(const std::vector<std::vector<ll>> & profitMatrix) 
{
    const ll INF = std::numeric_limits<ll>::max();

    int n = profitMatrix.size();
    int m = profitMatrix[0].size();
    int dim = std::max(n , m);

    ll maxVal = -INF;
    for (const auto & row : profitMatrix)
        for (ll val : row)
            maxVal = std::max(maxVal , val);

    std::vector<std::vector<ll>> cost(dim, std::vector<ll>(dim , maxVal));
    for (int i = 0 ; i < n ; ++i)
        for (int j = 0 ; j < m ; ++j)
            cost[i][j] = maxVal - profitMatrix[i][j];

    std::vector<ll> u(dim), v(dim);
    std::vector<int> p(dim), way(dim);

    for (int i = 1 ; i < dim ; ++i) {
        p[0] = i ;
        std::vector<ll> minv(dim, INF);
        std::vector<bool> used(dim);
        int j0 = 0;
        do 
        {
            used[j0] = true;
            int i0 = p[j0], j1; 
            ll delta = INF;
            for (int j = 1 ; j < dim ; ++j) 
            {
                if (!used[j]) 
                {
                    ll cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0 ; j < dim ; ++j) 
            {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
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
    for (int j = 1; j < dim; ++j)
        if (p[j] < n && j < m)
            result[p[j]] = j;

    return result;
}
std::vector<std::vector<ll>> Scenario3::buildProfitMatrix(Controler & control)
{
    int n = control.getBirds().size();
    int m = options.size();

    std::vector<std::vector<ll>> profit(n, std::vector<ll>(m, -1e9)); 

    for (int j = 0 ; j < m ; ++j) 
    {
        const auto& option = options[j];
        profit[option.birdIdx][j] = option.damage;
    }

    return profit;
}