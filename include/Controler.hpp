#ifndef CONTROLER_H
#define CONTROLER_H

#include "Missile.hpp"


#include <vector>


class Controler
{
    public:
        Controler();
        void readMissiles();


    private:
        std::vector<Missile> missiles;

};






#endif