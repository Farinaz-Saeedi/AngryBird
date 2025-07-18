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
void Scenario7::readInputs(std::vector<Bird> &birds, std::vector<Home> &homes)
{
    std::ifstream input("Scenario7.txt");
    if (!input.is_open())
        std::cerr << " Unable to open file ! \n";

    int cp, nights;
    ll count;
    ld p;
    std::string name;

    while (!input.eof())
    {
        input >> nights;
        setNumberOfNights(nights);

        input >> count;
        for (int i = 0; i < count; i++)
        {
            input >> name;
            input >> p;
            readBird(name, birds);

            lst.push_back({name, p});

            input >> name;
            input >> cp;
            readHome(name, cp, homes);
        }
    }

    input.close();
}