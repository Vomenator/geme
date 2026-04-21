#pragma once
#include <iostream>
#include <string>
//#include <cstdlib>
#include <vector>
#include <thread>

// this gets keyboard input
#include <windows.h>

// for future seeding
#include <random>
#include <vector>

// fill array
#include <algorithm>

#include "entity.hpp"
#include "tiles.hpp"

// --sectorScreenDimesions--
#define MAX_DRAW_X 32
#define MAX_DRAW_Y 32


// object structures


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

bool paintstart();
void paintPlayer(int shfR = 0);


void screenshake();


// --extern--

extern int final, pfinal;

// --entity info--

// -- tiles.cpp
//extern tile randomfloorchar();
//extern tile paintObject(int input);

//-- chunkGeneration.cpp --
extern bool randomchunk();
extern bool ishealthgood();