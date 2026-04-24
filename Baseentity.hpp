#pragma once
#include "basetypes.hpp"

struct entity : properties {
};

struct player : entity {
    bool ifalreadylock = false;
    static Fvector pos;
    static int credits;
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
    void changeisalreadylock() {
        ifalreadylock = !ifalreadylock;
        ifalreadylock = ifalreadylock ? true : false;
    }
    bool checkifplayerlocks() {
        return ifalreadylock;
    }
    virtual ~player() = default;
};



// --externs--

extern player playerinfo;
extern entity entityinfo;