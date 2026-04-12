#include "common.hpp"


//std::vector<std::vector<std::string>> chunks;

//std::vector<std::vector<char>> matrix(MAX_DRAW_Y, vector<std::string>)

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

bool collisionMatrix(int x = 0, int y = 0) {
    if ()
}

void getkeyinput() {
    while (true) {
        if(GetKeyState(VK_RIGHT) & 0x8000) {
            //std::cout << x << "\n";
            if (x < MAX_DRAW_X-1 && collisionMatrix(x) == false) x++;
            paintPlayer();
            keyprison(VK_RIGHT);
        }
        if(GetKeyState(VK_LEFT) & 0x8000) {
            //std::cout << x;
            if (x > 0) x--;
            paintPlayer();
            keyprison(VK_LEFT);
        }
        if(GetKeyState(VK_UP) & 0x8000) {
            //std::cout << x;
            if (y > 0) y--;
            paintPlayer();
            keyprison(VK_UP);
        }
        if(GetKeyState(VK_DOWN) & 0x8000) {
            //std::cout << y << '\n';
            if ((y*MAX_DRAW_X+1) < ((MAX_DRAW_Y-1)*MAX_DRAW_X)) y++;
            paintPlayer();
            keyprison(VK_DOWN);
        }
        if(GetKeyState(VK_F1) & 0x8000) {
            screenshake();
            //keyprison(VK_F1);
        }
    }
}


int main() {
    //std::thread(paintchunk).detach();
    std::thread(getkeyinput).detach();
    paintstart();
    while (true) {

    }
    return 0;
}

 
//~!@#$$%%^^&*()_+-=`|{[]}:;'"",<.>/?