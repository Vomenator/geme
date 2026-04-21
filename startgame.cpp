#include "common.hpp"

properties Tproperties;
player playerinfo;            // same with this 
Fvector player::pos = {0, 0}; // stupid stupid compiler winges without this RIP

bool ishealthgood() {
    if (playerinfo.currentship->health <= 0) {
        return false;
    }
    return true;
}

int entryPoint() {
    playerinfo.currentship = new ship::harlowclass;
    paintstart(); 
    while (ishealthgood()) {

    }
    return 1;
}