#include "common.hpp"


tile whereami[(MAX_DRAW_X*MAX_DRAW_Y) + 1];

std::vector<std::string> shakie;

// coordinates
int final = 0, pfinal = 0;
                                                                                    // makes randomised chunk


void paintchunk(int clear = 0) {
    //std::cout << "\033[44m";
    std::cout << "\033[3J\033[H";
    //std::cout << "\r" <<  "\033[2J\033[1;1H";

        std::string border = "\033[1m+";

    for (int i = 0; i <= MAX_DRAW_X-1; i++) {
        //std::cout << "\r" << "-" << std::flush;
        border += "--";

    }
    std::cout << "\r" << border << "+\033[0m\n" << std::flush;

    for (int i = 0; i <= (MAX_DRAW_X * MAX_DRAW_Y); i++)
    {
        //if (i / MAX_DRAW_X > MAX_DRAW_Y) std::cerr << "y is out of bounds\n"; return;
        if (i > 0 && (i % MAX_DRAW_X) == 0) {
            //std::cout << (clear, ' ') <<"\n";
            std::cout << "\033[1m|\033[0m" <<"\n" << "\033[1m|\033[0m";
        }
        if (i == 0) {
            std::cout << "\033[1m|\033[0m" << std::flush;
        }
        //std::cout << " " << chunk[i].display << std::flush;
        std::cout << " " << whereami[i].display << std::flush;          //this fine
    }
    std::cout << "\r" << border << "+\033[0m" << std::flush;
    //std::cout << (clear, ' ') << "\n" << chunk.size() << "\n";
    //std::cout << (clear, ' ') << "\n" << MAX_DRAW_X*MAX_DRAW_Y << "\n";
    //std::cout << "\nMAX_DRAW_X: " << MAX_DRAW_X << "\n MAX_DRAW_Y: " << MAX_DRAW_Y << "\n";
    std::cout << "\nhealth: " << playerinfo.currentship->health << "\n Fuel: " << playerinfo.currentship->fuel << "\n";
    std::cout << "\n\n\n\n\n";
}

void paintPlayer(int shfR) { 
    tile playerTile = {"\033[1;33m@\033[0m", false, &Tproperties};
    

    for (int i = 0; i < (MAX_DRAW_X * MAX_DRAW_Y); i++)
    {
        whereami[i] = chunk[i];
    }
    //whereami[0] = (((MAX_DRAW_X+1)*MAX_DRAW_Y), 'A');
    final = playerinfo.pos.x + (playerinfo.pos.y * MAX_DRAW_X);

    if (final >= 0 && final < (MAX_DRAW_X * MAX_DRAW_Y)) {
        //whereami[final] = "\033[1;33m@\033[0m";
        whereami[final] = playerTile;
        pfinal = final;
    }
    paintchunk(shfR);
}

void hidecursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// -- potential screenshake -- 

void screenshift(int severity) {
    for (int i = 0; i < chunk.size(); i++)
    {
        if (i == 0) {
            std::cout << (severity, " ");
        }
        if (i > 0 && (i % (MAX_DRAW_X)) == 0) {
            std::cout << "\n" << (severity, " ");
        }
        //std::cout << std::flush << chunk[i];
        //std::cout << whereami[i];
    }
    for (int i = 0; i <= MAX_DRAW_Y; i++) {
        std::cout << "\033[F";
    }
}


void screenshake() {
    screenshift(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    paintPlayer(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    screenshift(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    paintPlayer(3);
    
}

void paintscreen() {
    std::cout << "\033[3J\033[H";
    paintPlayer();
}

bool paintstart() {
    if(!randomchunk()) return false;
    hidecursor();
    //paintchunk();
    paintscreen();
    return true;
}