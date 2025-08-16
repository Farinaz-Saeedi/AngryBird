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
    ld totalDamage = 0;
    ll totalCost = 0;
    int consecutiveHighDamage = 0;
    const ld lambda = 0.1;

    for (int night = 1; night <= getNumberOfNights(); night++)
    {
        std::cout << "\nNight " << night << " begins ...\n\n";

        for (auto &home : homes)
        {
            auto myHome = std::dynamic_pointer_cast<Home>(home);
            if (!myHome)
                continue;

            for (auto &bird : myHome->getMyBirds())
            {
                for (auto &enemy : control.getEnemies())
                {
                    auto myEnemy = std::dynamic_pointer_cast<Enemy>(enemy);
                    ld dmg = bird.getDemolition();
                    ld cost = 0;

                    for (auto &it : lst)
                    {
                        if (it.first == bird.getName())
                        {
                            cost = it.second;
                            break;
                        }
                    }

                    int dgr = bird.getDegree();
                    if (dmg > 0)
                    {
                        options.push_back({&bird, myHome, myEnemy, dmg, cost, dgr});
                    }
                }
            }
        }

        if (options.empty())
        {
            std::cout << "No launches possible this night.\n";
            continue;
        }

        std::sort(options.begin(), options.end(), [&, lambda](OptionScen7 &a, OptionScen7 &b)
                  {
            ld valA = a.expectedDamage * (1.0 - 1.0 / a.radarLevel) - lambda * a.cost;
            ld valB = b.expectedDamage * (1.0 - 1.0 / b.radarLevel) - lambda * b.cost;

            if(a.radarLevel != b.radarLevel) return a.radarLevel < b.radarLevel;
            return valA > valB; });

        ld nightDamage = 0;
        ll nightCost = 0;
        std::unordered_map<std::string, int> defenseCounter;

        for (auto &opt : options)
        {
            std::string targetName = opt.target->getCityName();
            int defense = opt.target->getDefenseLevel();
            if (defenseCounter[targetName] >= defense)
                break;

            ld survivalProb = 1.0 - (defenseCounter[targetName] < defense ? 0.0 : 1.0 / opt.radarLevel);
            survivalProb = std::clamp(survivalProb, (ld)0.0, (ld)1.0);

            ld actualDamage = opt.expectedDamage * survivalProb;
            nightDamage += actualDamage;
            nightCost += opt.cost;

            std::cout << "Launch " << opt.bird->getName()
                      << " from " << opt.home->getCityName()
                      << " to " << targetName
                      << " | Damage: " << actualDamage
                      << " | Cost: " << opt.cost
                      << " | SurvivalProb: " << survivalProb << "\n";

            auto tempHome = std::dynamic_pointer_cast<Home>(opt.home);
            auto &birdsList = tempHome->getMyBirds();

            birdsList.erase(std::remove_if(birdsList.begin(), birdsList.end(),
                                           [&](Bird &b)
                                           { return b.getName() == opt.bird->getName(); }),
                            birdsList.end());

            defenseCounter[targetName]++;
        }

        totalDamage += nightDamage;
        totalCost += nightCost;

        if (nightDamage >= damage)
            consecutiveHighDamage++;
        else
            consecutiveHighDamage = 0;

        if (consecutiveHighDamage >= 7)
        {
            std::cout << "\nEnemy surrendered after 7 nights with high damage!\n";
            break;
        }
        std::cout << "Night damage: " << nightDamage
                  << " | Night cost: " << nightCost << "\n";
    }

    std::cout << "\n=== Total Damage: " << totalDamage
              << " | Total Cost: " << totalCost << " ===\n";
}