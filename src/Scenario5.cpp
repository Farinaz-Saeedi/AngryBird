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
    for (int i = 1; i <= getNumberOfNights(); i++)
    {
        std::cout << "\nNight " << i << " begins...\n";

        ld totalDamage = 0.0;

        for (auto &home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (!myHome)
                continue;

            auto &birds = myHome->getMyBirds();
            if (birds.empty())
                continue;

            for (int j = 0; birds.size(); j++)
            {
                Bird & bird = birds[j];
                std::string enemy = control.findBestPairFor(home, bird);
                if (enemy.empty())
                    continue;
                
                auto path = control.aStar(home->getCityName(), enemy, bird);
                if (path.empty())
                    continue;
                
                totalDamage += control.totoalDamage(path, bird);

                std::cout << "-----------------------------\n";
                std::cout << "\nBird : " << bird.getName() << "\nPath: ";
                for (auto &city : path)
                {
                    std::cout << city->getCityName() << " ";
                }
                std::cout << "\n";

                birds.erase(birds.begin() + j);
            }
        }
        std::cout << "\n-----------------------------\n";
        std::cout << "\nTotal Damage (Neight "<< i <<" ): " << totalDamage << "\n";

        control.newSpies();
    }

    
}