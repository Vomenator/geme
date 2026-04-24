#pragma once
#include "basetypes.hpp"
#include "tiles.hpp"

//------------------------- boiler plate stuff ----------------------------

inline bool ischarfloorvalid(std::string previous, std::string input) {   //_-|\\/#
    if (previous == "\n") return true;
    if (input == ".") {
        //switch (previous) {
       //     case ".":
       //         return true;
      //      default:
       //         return false;
       // }
    }
    return true;
}


inline int genrandomNum(int max) {
    std::random_device rd;
    std::mt19937 gen(rd()); // this is what it is seeded by
    std::uniform_int_distribution<> dist(0, max); // range
    return dist(gen);
}
// forward declarations

int entryPoint();
void doturn();
bool paintstart();
void paintscreen();
void dontupdatemepaint();
//void paintPlayer(int shfR = 0);

void paintprojectile(int targetX, int targetY);

void screenshake();


// --extern--

extern int final, pfinal;

extern properties Tproperties;
extern std::vector<tile> chunk;
extern std::vector<tile> whereami;


// --entity info--

// -- tiles.cpp
//extern tile randomfloorchar();
//extern tile paintObject(int input);

//-- chunkGeneration.cpp --
extern bool randomchunk();
extern bool ishealthgood();