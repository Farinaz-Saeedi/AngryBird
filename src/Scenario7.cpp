#include "Scenario7.hpp"

int Scenario7::getNumberOfNights()
{
    return numberOfNights;
}
void Scenario7::setNumberOfNights(int numberOfNights)
{
    this->numberOfNights = numberOfNights;
}
void Scenario7::setDamage(ld damage)
{
    this->damage = damage;
}
ld Scenario7::getDamage()
{
    return damage;
}
void Scenario7::readInputs(std::vector<Bird> &birds, std::vector<std::shared_ptr<City>> &homes)
{
    std::ifstream input("../src/Scenario7.txt");
    if (!input.is_open())
        std::cerr << " Unable to open Scen-7 file ! \n";

    int nights;
    ll count;
    ld temp;
    std::string name;

    while (!input.eof())
    {
        input >> nights >> temp;
        setNumberOfNights(nights);
        setDamage(temp);

        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> temp;
            Bird tempBird = readBird(name, birds);

            lst.push_back({name, temp});

            input >> name;
            birds[birds.size() - 1].setHomePlace(name);

            for (int j = 0; j < homes.size(); j++)
            {
                auto home = std::dynamic_pointer_cast<Home>(homes[j]);
                if (home->getCityName() == name)
                {
                    home->push(tempBird);
                    break;
                }
            }
        }
    }

    input.close();
}
void Scenario7::printOutput(Controler &control, std::vector<std::shared_ptr<City>> &homes)
{
}

std::vector<OptionScen7> Scenario7::knapsackMinCost(const std::vector<OptionScen7> &options, ld damageThreshold)
{
    int n = options.size();
    std::vector<OptionScen7> bestSelection;
    ld bestCost = 1e18;
    ld currentDamage = 0;

    std::vector<OptionScen7> sortedOptions = options;
    std::sort(sortedOptions.begin(), sortedOptions.end(), [](const OptionScen7 &a, const OptionScen7 &b)
    { 
        return (a.damage / a.cost) > (b.damage / b.cost); 
    });

    for (auto &opt : sortedOptions)
    {
        bestSelection.push_back(opt);

        currentDamage += opt.damage;
        if (currentDamage >= damageThreshold)
            break;
    }

    return bestSelection;
}


