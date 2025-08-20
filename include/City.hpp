#ifndef CITY_H
#define CITY_H

#include <string>

#define ll long long
#define ld long double

enum Status
{
    N, E, H
};

class City
{
    public:
        virtual ~City() = default;
        City();
        City(std::string name, ld x, ld y, bool is);
        std::string getCityName();
        Status getStatus();
        ld getX();
        ld getY();
        bool getIsSpy();
        void setCityName(std::string countryName);
        void setStatus(Status status);
        void setX(ld x);
        void setY(ld y);
        void setIsSpy(bool isSpy);

    private:
        std::string cityName;
        Status status; // Normal City - Enemy City - Home Base
        ld x;
        ld y;
        bool isSpy;
};

#endif