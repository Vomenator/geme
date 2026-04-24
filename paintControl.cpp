#include "common.hpp"
#include "tiles.hpp"

//tile whereami[(MAX_DRAW_X*MAX_DRAW_Y) + 1];
std::vector<tile> whereami;
std::vector<tile> VFXlayer;
std::string screen;

//std::vector<std::string> shakie;

std::string sectorbordertop = "\033[1m+";
std::string secondarybordertop = "\033[1m+-----------------------------------------+\033[0m";

int currentline = 0;

int sideinfomaxline = 54;

tile playerTile;

// forward declaration

std::string paintplayershipinfo();
// coordinates
int final = 0, pfinal = 0;
                                                                                    // makes randomised chunk
void clearscreen() {
    currentline = 0;
    std::cout << "\033[2B";                                 // goes down 2 rows
    std::cout << "\033[3J\033[H";                           // then goes to home
    //screen = "";
}

void delay(int delayms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
}

void movecursor(int x = 0, int y = 0) {
    std::cout << "\033[3J\033[H";

    if (x != 0) {
        x *= 2;
        std::cout << "\033[" << x << "C";
    }
    if (y != 0) {
        std::cout << "\033["<< y << "B";
    }
}

void initborders() {
    for (int i = 0; i <= MAX_DRAW_X-1; i++) {
        //std::cout << "\r" << "-" << std::flush;
        sectorbordertop += "--";
    }
}

void paintchunk() {
    std::cout << screen << std::flush;          //this fine
    //movecursor(MAX_DRAW_X+1);
    //std::cout << paintplayershipinfo();
   // }
    //std::cout << "\r" << sectorbordertop << "+\033[0m" << std::flush;
}

void doublebufferme() {
    // split playerinfos into lines upfront
    std::string playerinfos = paintplayershipinfo();
    std::vector<std::string> infolines;
    std::string tmp;

    for (char c : playerinfos) {
        if (c == '\n') {
            infolines.push_back(tmp);
            tmp.clear();
        } else {
            tmp += c;
        }
    }
    if (!tmp.empty()) infolines.push_back(tmp);

    int infoline = 0;

    auto getnextinfoline = [&]() -> std::string {
        if (infoline < infolines.size()) return infolines[infoline++];
        return "";
    };

    screen = sectorbordertop + getnextinfoline() + "\033[0m\n";

    for (int i = 0; i < (int)whereami.size(); i++) {
        if (i == 0) {
            screen += "\033[1m|\033[0m";
        }

        if (i > 0 && (i % MAX_DRAW_X) == 0) {
            screen += "\033[1m|\033[0m  " + getnextinfoline() + "\n\033[1m|\033[0m";
        }

        screen += " " + whereami[i].display;
    }

    screen += "\033[1m|\033[0m  " + getnextinfoline() + "\n";
    screen += sectorbordertop + "+\033[0m\n";
}

void paintPlayer() {
    whereami.clear(); 
    playerTile = {"\033[1;33m@\033[0m", false, &Tproperties};
    

    for (int i = 0; i < (MAX_DRAW_X * MAX_DRAW_Y); i++)
    {
        whereami.push_back(VFXlayer[i]);
    }
    //whereami[0] = (((MAX_DRAW_X+1)*MAX_DRAW_Y), 'A');
    final = playerinfo.pos.x + (playerinfo.pos.y * MAX_DRAW_X);

    if (final >= 0 && final < (MAX_DRAW_X * MAX_DRAW_Y)) {
        //whereami[final] = "\033[1;33m@\033[0m";
        whereami[final] = playerTile;
        pfinal = final;
    }
    //paintchunk();
}

void hidecursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int parametermath(float value, float maxvalue, int sizebar = 10) {
    int finalbar = (value / maxvalue) * sizebar;
    return finalbar;
}

std::string makebar(std::string barcolour, std::string empty_colour, int current, int max) {
    int barvalue = parametermath(current, max);
    std::string bar;
    char ranonce = 0x00;
    for (int i = 0; i < 10; i++) {

        if (i < barvalue) {
            bar += "\033[" + barcolour + "=\033[0m";
        }
        else {
            if (current < 10 && current != 0 && ranonce == 0x00) {
                bar += "\033[" + barcolour + "\x1b[6m=\033[0m";
                ranonce = 0x01;
            }
            if (ranonce != 0x00 && i == 9) break;
            bar += "\033[" + empty_colour + "-\033[0m";
        }
    }
    return bar;
}

std::string makefield(std::string label, std::string bar, int current, int max) {
    std::string currentvalue = std::to_string(current);
    if (current < 100) {
        currentvalue = "0" + std::to_string(current);
    }
    return "      " + label + " [" + bar + "] " + currentvalue + "/" + std::to_string(max);
}


std::string paintplayershipinfo() {
    auto ship = playerinfo.currentship;

    std::string healthbar = makebar("1;33m", "37;90m", ship->health,  ship->maxhealth);
    std::string fuelbar   = makebar("1;36m", "37;90m", ship->fuel,    ship->maxfuel);
    std::string ammobar   = makebar("1;32m", "37;90m", ship->ammo,    ship->maxammo);

    std::string full = secondarybordertop + "\n";
    full += "       \033[1;33m" + ship->name + "  //  " + ship->Shipclass + "\033[0m\n";
    full += makefield("HULL ", healthbar, ship->health,  ship->maxhealth) + "\n";
    full += makefield("FUEL ", fuelbar,   ship->fuel,    ship->maxfuel)   + "\n";
    full += makefield("AMMO ", ammobar,   ship->ammo,    ship->maxammo)   + "\n";

    return full;
}

void makeVFXlayer() {
    VFXlayer.clear();
    for (int i = 0; i < (MAX_DRAW_X * MAX_DRAW_Y); i++)
    {
        VFXlayer.push_back(chunk[i]);
    }
}

Fvector normalise(int targetX, int targetY) {
    int dx = targetX - playerinfo.pos.x;
    int dy = targetY - playerinfo.pos.y;
    float distance = sqrt((dx * dx) + (dy * dy));
    float nx = dx / distance;
    float ny = dy / distance;

    return {nx, ny};
}

void paintprojectile(int targetX, int targetY) {
    float projX = playerinfo.pos.x;
    float projY = playerinfo.pos.y;
    Fvector normalised = normalise(targetX, targetY);
    int i = 0;
    while (true) {
        if (i > 0 && i %2) paintscreen();
        projX += normalised.x;
        projY += normalised.y;

        int tileX = (int)round(projX);
        int tileY = (int)round(projY);
        int index = tileX + (tileY * MAX_DRAW_X);

        // bounds check
        if (tileX < 0 || tileX >= MAX_DRAW_X || tileY < 0 || tileY >= MAX_DRAW_Y) break;

        // hit something
        if (chunk[index].collidable) {
            paintscreen();
            // apply damage to chunk[index].Otherproperties
            break;
        }

        // reached target
        if (tileX == targetX && tileY == targetY) {
            // hit the locked target
            paintscreen();
            break;
        }
        else {
            whereami[index].display = "@";
            dontupdatemepaint();
            delay(15);
        }
        i++;
    }
}



void dontupdatemepaint() {
    clearscreen();
    doublebufferme();
    paintchunk();
}

void paintscreen() {
    clearscreen();
    makeVFXlayer();
    paintPlayer();
    doublebufferme();
    paintchunk();
    //std::cout << makebar("1;33m", "37;91m", playerinfo.currentship->health, playerinfo.currentship->maxhealth);
    //movecursor((MAX_DRAW_X+1));
    //paintplayerinfo();

}

bool paintstart() {
    if(!randomchunk()) return false;
    hidecursor();
    initborders();
    paintscreen();
    return true;
}