#pragma once
#include "Baseentity.hpp"

//enum class exploreclasstype {
//    wayfinder,
//};

// this is the structure data for all of the inanimate tiles out there :) we are very inclusive

// and this crap aswell otherwise the compiler has a meltdown


// properties of the tiles

struct objects : properties {
    virtual void OnPlayerinteract(tile& t, player& p) {}
};


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class asteroid {
    public:
        struct tinyasteroid : objects {
            bool locked = false;
            void Onspawn(tile& t) {
                t.display = "\033[90m#\033[0m";
                t.collidable = true;
            }
            void OnPlayerinteract(tile& t, player& p) override {
                if (locked == true && p.checkifplayerlocks() == true) {
                    locked = false;
                    p.changeisalreadylock();
                }
                else if (locked == false && p.checkifplayerlocks() == false) {
                    locked = true;
                    p.changeisalreadylock();
                }
                else {
                    return;
                }
                t.display = locked ? "\033[1;97m*\033[0m" : "\033[90m#\033[0m";
                //t.display = '@';
               //std::cout << "helloworld";
            }
        };
};

// -- externs --