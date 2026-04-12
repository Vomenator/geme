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

#define MAX_DRAW_X 32
#define MAX_DRAW_Y 32


// --extern--

// coordinates

typedef struct vector {
    int x = 0;
    int y = 0;
} vector;

extern int x, y;
extern int final, pfinal;

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

// forward declarations

void paintstart();
void paintPlayer(int shfR = 0);


void screenshake();