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
            readBird(name, birds);

            lst.push_back({name, temp});

            input >> name;
            input >> cp;
            readHome(name, cp, homes);
        }
    }

    input.close();
}