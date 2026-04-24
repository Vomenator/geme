#include "common.hpp"
#include "tiles.hpp"

HANDLE hinput;

//std::vector<std::vector<std::string>> chunks;

//std::vector<std::vector<char>> matrix(MAX_DRAW_Y, vector<std::string>)

struct colresult {
    int x;
    int y;
};

Fvector lockedlocation;

// --keypress logic--
void keyprison(char input) {
    while (true) {
        if ((GetKeyState(input) & 0x8000) == 0) {
            break;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            break;
        }
    }
}

bool isfuelgood() {
    if (playerinfo.currentship->fuel > 0) {
        return true;
    }
    return false;
}

bool canmove() {
    if (isfuelgood() == false) return false;
    if (ishealthgood() == false) return false;
    return true;
}

colresult amicolliding(int x, int y) {
    int final = x + (y * MAX_DRAW_X);
    int resultX = 0;
    int resultY = 0;
    // edgecase funtime

    // right
    if (x < MAX_DRAW_X - 1) {
        //std::cout << "Collision at (" << x+1 << ", " << y+1 << "): " << "1" << std::endl;
        if (!chunk[final + 1].collidable) resultX += 1;
    }
    // left
    if (x > 0) {
        //std::cout << "Collision at (" << x-1 << ", " << y+1 << "): " << "2" << std::endl;
        if (!chunk[final - 1].collidable) resultX += 2;
    }
    // down
    if (final >= MAX_DRAW_X) {
        //std::cout << "Collision at (" << x+1 << ", " << y+1 << "): " << "4" << std::endl;
        if (!chunk[(final - MAX_DRAW_X)].collidable) resultY += 1;
    }
    // up
    if ((final + MAX_DRAW_X) < (MAX_DRAW_X * MAX_DRAW_Y)) {
        //std::cout << "Collision at (" << x+1 << ", " << y+1 << "): " << "3" << std::endl;
        if (!chunk[(final + MAX_DRAW_X)].collidable) resultY += 2;
    }
    return {resultX, resultY};
}

void getkeyinput() {
    while (true) {
        if(GetKeyState(VK_RIGHT) & 0x8000) {
            colresult resultxy = amicolliding(playerinfo.pos.x, playerinfo.pos.y);
            //std::cout << resultxy.x << "\n";
            //std::cout << x << "\n";
            if (playerinfo.pos.x < MAX_DRAW_X-1 && (((resultxy.x) == 3 || (resultxy.x) == 1) && canmove() == true)) {
                playerinfo.pos.x++; 
                playerinfo.consumefuel();
            }
                
            doturn();
            keyprison(VK_RIGHT);
        }

        if(GetKeyState(VK_LEFT) & 0x8000) {
            colresult resultxy = amicolliding(playerinfo.pos.x, playerinfo.pos.y);
            //std::cout << resultxy.x << "\n";
            //std::cout << x;
            if (playerinfo.pos.x > 0 && (((resultxy.x) == 3 || (resultxy.x) == 2) && canmove() == true)) {
                playerinfo.pos.x--; 
                playerinfo.consumefuel();
            }
            doturn();
            keyprison(VK_LEFT);
        }

        if(GetKeyState(VK_UP) & 0x8000) {
            colresult resultxy = amicolliding(playerinfo.pos.x, playerinfo.pos.y);
            //std::cout << "\n" << resultxy.y << "\n";
            //std::cout << x;
            if (playerinfo.pos.y > 0 && (((resultxy.y) == 3 || (resultxy.y) == 1) && canmove() == true)) {
                playerinfo.pos.y--; 
                playerinfo.consumefuel();
            }
            doturn();
            keyprison(VK_UP);
        }

        if(GetKeyState(VK_DOWN) & 0x8000) {
            colresult resultxy = amicolliding(playerinfo.pos.x, playerinfo.pos.y);
            //std::cout << "\n" << resultxy.y << "\n";
            //std::cout << y << '\n';
            if ((playerinfo.pos.y*MAX_DRAW_X+1) < ((MAX_DRAW_Y-1)*MAX_DRAW_X) && (((resultxy.y) == 3 || (resultxy.y) == 2) && canmove() == true)) {
                playerinfo.pos.y++;
                playerinfo.consumefuel();
            }
            doturn();
            keyprison(VK_DOWN);
        }

        if(GetKeyState(VK_SPACE) & 0x8000) {
            if (playerinfo.ifalreadylock == true) paintprojectile(lockedlocation.x,lockedlocation.y);
            keyprison(VK_SPACE);
        }
    }
}

void startmouseinput() {
    std::cout << "\033[?1003h"; // ALL mouse movement reporting
    std::cout << "\033[?1006h"; // extended mode (needed for terminals wider than 223 cols)
    DWORD mode;
    GetConsoleMode(hinput, &mode);
    SetConsoleMode(hinput, mode |(ENABLE_MOUSE_INPUT & ~ENABLE_QUICK_EDIT_MODE));
}

void parsemouse() {
    INPUT_RECORD record;
    DWORD events;

    while (true) {
        //std::cout << "hello world!";
        ReadConsoleInput(hinput, &record, 1, &events);
        if (record.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD m = record.Event.MouseEvent;
            int x = ((m.dwMousePosition.X)-1)/2;
            int y = ((m.dwMousePosition.Y))-1;

            if (m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                int locatehover = (y*MAX_DRAW_X) + x;

                if (locatehover < chunk.size() && x < MAX_DRAW_X) {
                    //std::cout << "locatehover: " << x << "y: " << y;
                    //std::cout << "Otherproperties: " << chunk[locatehover].Otherproperties << "\n";
                    if (chunk[locatehover].Otherproperties != nullptr) {
                        objects* obj = dynamic_cast<objects*>(chunk[locatehover].Otherproperties);
                        obj->OnPlayerinteract(chunk[locatehover], playerinfo);
                        lockedlocation.x = x;
                        lockedlocation.y = y;
                    }
                    paintscreen();
                }
            }
        }
    }
}

int main() {
    hinput = GetStdHandle(STD_INPUT_HANDLE);
    startmouseinput();
    std::thread(parsemouse).detach();
    std::thread(getkeyinput).detach();
    //paintstart();       //defs tjos
    entryPoint();
}

 
//~!@#$$%%^^&*()_+-=`|{[]}:;'"",<.>/?