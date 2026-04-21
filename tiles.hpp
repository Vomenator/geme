#pragma once
#include "common.hpp"

// this is the structure data for all of the inanimate tiles out there :) we are very inclusive

// and this crap aswell otherwise the compiler has a meltdown
typedef struct Fvector {
    int x = 0;
    int y = 0;
} Fvector;

// properties of the tiles

typedef struct properties {

} properties;

//------------------------- main tile stucture ----------------------------

typedef struct tile {
    std::string display;
    bool collidable;
    properties* Otherproperties = nullptr;
} tile;

extern properties Tproperties;
extern std::vector<tile> chunk;





//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ship {
    public:
        struct shiptype {
            std::string name;
            int health = 0;
            int fuel = 0;
            virtual ~shiptype() = default;
        };

        struct harlowclass : shiptype {
            harlowclass() {
                name = "harlow";
                health = 100;
                fuel = 100;
            }
        };
};

// -- externs --