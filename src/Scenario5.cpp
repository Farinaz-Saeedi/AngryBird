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

std::vector<std::vector<Bird>> Scenario5::distributeBirds(Controler &control)
{
    std::vector<Bird> allBirds = control.getBirds();

    std::sort(allBirds.begin(), allBirds.end(), [](Bird &a, Bird &b)
              { return a.getDemolition() > b.getDemolition(); });

    int n = allBirds.size();
    int nights = getNumberOfNights();

    int base = n / nights;
    int extra = n % nights;

    std::vector<std::vector<Bird>> birdsByNight(nights);
    int index = 0;

    for (int i = 0; i < nights; ++i)
    {
        int count = base + (i == 0 ? extra : 0); 
        birdsByNight[i].insert(birdsByNight[i].end(), allBirds.begin() + index, allBirds.begin() + index + count);
        index += count;
    }

    return birdsByNight;
}

void Scenario5::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
    // for (int i = 1; i <= getNumberOfNights(); i++)
    // {
    //     std::cout << "\nNight " << i << " begins...\n";

    //     ld totalDamage = 0.0;
    //     for (auto &home : homes)
    //     {
    //         auto myHome = std::dynamic_pointer_cast<Home>(home);
    //         if (!myHome)
    //             continue;

    //         auto &birds = myHome->getMyBirds();
    //         if (birds.empty())
    //             continue;

    //         for (auto &bird : birds)
    //         {
    //             ll distance = 0;
    //             std::vector<std::shared_ptr<City>> path;
    //             auto [enemy, canDestroy] = control.findBestPairFor(home, bird, path, distance);

    //             std::cout << "Bird : " << bird.getName() << "\nPath: ";

    //             if (canDestroy != 1)
    //                 control.deadBird(bird, distance);
    //             else
    //             {
    //                 control.setReachBird(enemy, bird, path);
    //                 for (auto &city : path)
    //                 {
    //                     std::cout << city->getCityName() << " ";
    //                 }
    //             }
    //             std::cout << "\n---------------------------------------\n";
    //             std::cout << "\n";
    //         }
    //     }

    //     std::cout << "\n---------------------------------------\n";

    //     control.attack();

    //     auto birds = control.getBirds();
    //     for (auto &bird : birds)
    //     {
    //         totalDamage += bird.getDemolition();
    //     }

    //     std::cout << "---------------------------------------";
    //     std::cout << "\nTotal Damage (Neight " << i << " ): " << totalDamage << "\n";

    //     std::cout << "---------------------------------------\n";
    //     control.newSpies();
    // }
}