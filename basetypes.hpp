#pragma once
#include <iostream>
#include <string>
//#include <cstdlib>
#include <vector>

// this gets keyboard input
#include <windows.h>

// for future seeding
#include <random>
#include <chrono>
#include <thread>

// fill array
#include <algorithm>

// --sectorScreenDimesions--
#define MAX_DRAW_X 64
#define MAX_DRAW_Y 32


// object structures
typedef struct Fvector {
    float x = 0;
    float y = 0;
} Fvector;

typedef struct properties {
    virtual ~properties() = default;
} properties;

typedef struct tile {
    std::string display;
    bool collidable;
    properties* Otherproperties = nullptr;
} tile;

class ship {
    public:
        struct shiptype {
            std::string name;
            std::string Shipclass;
            int maxhealth = 0;
            int maxfuel = 0;
            int maxammo = 0;

            float health = 0;
            float fuel = 0;
            float ammo = 0;
            virtual ~shiptype() = default;
        };

        struct harlowclass : shiptype {
            harlowclass() {
                name = "ISV Harlow";
                Shipclass = "Wayfinder";
                maxhealth = 100;
                maxfuel = 100;
                maxammo = 100;

                health = 100;
                fuel = 100;
                ammo = 100;
            }
        };
};
