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

    for (int night = 1; night <= numberOfNights; ++night)
    {
        std::cout << "\nNight " << night << " begins ...\n\n";

        options.clear();

        for (auto &home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (!myHome)
                continue;

            auto &birds = myHome->getMyBirds();
            if (birds.empty())
                continue;

            for (int b = 0; b < birds.size(); b++)
            {
                Bird &bird = birds[b];

                for (auto &target : control.getEnemies())
                {
                    ll distance;
                    ld cost;
                    control.aStar(myHome->getCityName(), target->getCityName(), bird, path, distance, cost);

                    if (!path.empty())
                    {
                        ll dmg = bird.getDemolition();
                        options.push_back({b, bird.getDegree(), home, target, path, cost, dmg});
                    }
                }
            }
        }

        std::sort(options.begin(), options.end() , [](OptionScenario5 &a , OptionScenario5 &b)
        {
            if ( a.spyNum != b.spyNum)
                return a.spyNum < b.spyNum;
            return a.damage > b.damage;
        });

        std::cout << options.size() << '\n';

        for ( auto &opt : options)
        {
            if (control.isDetected(birds[opt.birdIdx])) continue;

            int idx = opt.birdIdx;
            if (idx >= 0 && idx < birds.size())
            {
                birds.erase(birds.begin() + idx);
            }
            std::cout << "---------------------------------------\n"
                      << "Bird: " << birds[opt.birdIdx].getName()  
                      << "\nFrom: " << opt.home->getCityName() << " | To: " << opt.target->getCityName() << "\nPath: ";
            for (auto &city : path)
            {
                std::cout << city->getCityName() << " ";
            }
            std::cout << "\n---------------------------------------";
            break;
        }

        if (options.empty())
        {
            std::cout << "No launches possible this night.\n";
            control.newSpies();

            continue;
        }

        control.newSpies();
    }

    std::cout << "-- Total Damage: " << totalDamage << " --\n";
}
