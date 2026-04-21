#pragma once
#include "tiles.hpp"

struct player : properties {
    static Fvector pos;
    ship::shiptype* currentship = nullptr;

    int consumefuel() {
        if (currentship->fuel > 0) {
            currentship->fuel -= 1;
        }
        return 0;
    }
    int healthloss() {
        if (currentship->health > 0) {
            currentship->health -= 10;
        }
        return 0;
    }
    virtual ~player() = default;
};


// --externs--

extern player playerinfo;