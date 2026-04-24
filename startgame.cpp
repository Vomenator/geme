#include "common.hpp"
#include "tiles.hpp"

properties Tproperties;
player playerinfo;            // same with this
objects objectinfo;            // same with this
entity entityinfo;
Fvector player::pos = {0, 0}; // stupid stupid compiler winges without this RIP

void doturn() {
    paintscreen();
}

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
    std::cout << "\033[?1003l";
    std::cout << "\033[?1006l";
    return 1;
}