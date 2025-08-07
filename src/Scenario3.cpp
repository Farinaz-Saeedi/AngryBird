#include "Scenario3.hpp"


void Scenario3::readInputs(std::vector<Bird> & birds , std::vector<std::shared_ptr<City>> & homes)
{
    std::ifstream input("../src/Scenario3.txt");
    if (!input.is_open())
    std::cerr << " Unable to open Scen-3 file ! \n";
    
    ll count, number;
    std::string name;

    while (!input.eof())
    {
        input >> count;
        setSlingshot(count);
        
        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> number;
            for (int i = 0; i < number; i++)
            {
                readBird(name, birds);
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
//     ld totalDamage = 0.0;

//     for (auto &bird : control.getBirds())
//     {
//         auto path = control.aStar(control.getTopBestPair().first, control.getTopBestPair().second, bird);

//         std::cout << "\nBird : " << bird.getName() << "\nPath: ";
//         for (auto &city : path)
//         {
//             std::cout << city << " ";
//         }

//         std::cout << "\n\n";
//         totalDamage += control.totoalDamage(path, bird);
//     }

//     std::cout << "Total Damage: " << totalDamage << "\n";
}
std::vector<AssignmentOption> Scenario3::assignOptions(Controler & controler , std::vector<std::shared_ptr<City>> & homes) 
{
    std::vector<AssignmentOption> options;

    std::vector<Bird> birds = controler.getBirds();
    std::vector<std::shared_ptr<City>> path;
    ll distance;

    for (int b = 0 ; b < birds.size() ; ++b) 
    {
        Bird bird = birds[b];

        for (auto & home : homes) 
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (myHome->getCapacity() == 0) continue;

            for (auto & target : controler.getEnemies()) 
            {
                controler.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance);

                if (!path.empty() && !controler.isDetected(bird))
                {
                    ll dmg = bird.getDemolition();  
                    options.push_back({bird, home, target, path, dmg});
                }
            }
        }
    }

    return options;
}
std::vector<int> Scenario3::hungarianMaximize(const std::vector<std::vector<double>> & profitMatrix) 
{
    const double INF = std::numeric_limits<double>::max();

    int n = profitMatrix.size();
    int m = profitMatrix[0].size();
    int dim = std::max(n , m);

    double maxVal = -INF;
    for (const auto & row : profitMatrix)
        for (double val : row)
            maxVal = std::max(maxVal , val);

    std::vector<std::vector<double>> cost(dim, std::vector<double>(dim , maxVal));
    for (int i = 0 ; i < n ; ++i)
        for (int j = 0 ; j < m ; ++j)
            cost[i][j] = maxVal - profitMatrix[i][j];

    std::vector<double> u(dim), v(dim);
    std::vector<int> p(dim), way(dim);

    for (int i = 1 ; i < dim ; ++i) {
        p[0] = i ;
        std::vector<double> minv(dim, INF);
        std::vector<bool> used(dim);
        int j0 = 0;
        do 
        {
            used[j0] = true;
            int i0 = p[j0], j1; 
            double delta = INF;
            for (int j = 1 ; j < dim ; ++j) 
            {
                if (!used[j]) 
                {
                    double cur = cost[i0][j] - u[i0] - v[j];
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