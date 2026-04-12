#include "common.hpp"

std::vector<std::string> chunk;
std::string whereami[(MAX_DRAW_X*MAX_DRAW_Y) + 1];

std::vector<std::string> shakie;

// coordinates
int x = 0, y = 0;
int final = 0, pfinal = 0;

                                                                                    // gets random character
std::string randomfloorchar() {                                //_-|\\/#&$^&*
    std::random_device rd;
    std::mt19937 gen(rd()); // this is what it is seeded by
    std::uniform_real_distribution<> dist(0, 12); // range 
    int result = dist(gen);
    //std::cout << result << " ";

    if (result <= 12) {
        return "\033[2;32m.\033[0m";
    }
    return "\0";
}

std::string paintObject(int input) {                                //_-|\\/#
    //std::cout << result << " ";

    if (input >= 150) {
        return "\033[1;32m#\033[0m";
    }
    return "\0";
}

void paintObjects() {
    std::random_device rd;
    std::mt19937 gen(rd()); // this is what it is seeded by
    std::uniform_int_distribution<> dist(0, 151); // range
    int incr = 0;
    for (int i = 0; i < MAX_DRAW_Y; i++) {
        for (int a = 0; a < MAX_DRAW_X; a++) {
                std::string result = paintObject(dist(gen));
                if (result != "\0") {
                    chunk[incr + a] = result;
                }  
        }
        incr += MAX_DRAW_X;
    }
}
                                                                                    // makes randomised chunk
bool randomchunk() {
    //int line = 1;
    std::string lines = "";
    //int incr = 0;
    for (int i = 0; i < MAX_DRAW_Y; i++) {
        for (int a = 0; a < MAX_DRAW_X; a++) {
            chunk.push_back(randomfloorchar());
            if ((a >= 2 && i != 0)) {
                //std::cout << incr;
                //if (!ischarfloorvalid(chunk[(incr + a) - 1], chunk[incr + a])) { // have to minus two as otherwise its reading \0
                    //std::cout << "invalid\n";
                   // lines.erase(incr + a);
                 //   a--;
              //  }
            }
            //std::cout << lines;
        }
        //chunk.push_back("\n"); // this is fine for now
        //std::cout << lines;
        //incr += MAX_DRAW_X-1;
    }
    //chunk.push_back(lines);
    //std::cout << lines;
    //paintPlayer();
    paintObjects();
    return true;
}


void paintchunk(int clear = 0) {
    //std::cout << "\033[44m";
    std::cout << "\033[3J\033[H";
    //std::cout << "\r" <<  "\033[2J\033[1;1H";
    for (int i = 0; i < chunk.size(); i++)
    {
        if (i > 0 && (i % (MAX_DRAW_X)) == 0) {
            std::cout << (clear, ' ') <<"\n";
        }
        //std::cout << std::flush << chunk[i];
        std::cout << " " << whereami[i] << std::flush;
    }
    std::cout << (clear, ' ') << "\n" << chunk.size() << "\n";
    std::cout << (clear, ' ') << "\n" << MAX_DRAW_X*MAX_DRAW_Y << "\n";
}

void paintPlayer(int shfR) {
    for (int i = 0; i < (MAX_DRAW_X*MAX_DRAW_Y); i++)
    {
        whereami[i] = chunk[i];
    }
    //whereami[0] = (((MAX_DRAW_X+1)*MAX_DRAW_Y), 'A');
    final = x + (y*(MAX_DRAW_X));

    if (final >= 0 && final < (MAX_DRAW_X * MAX_DRAW_Y)) {
        whereami[final] = "\033[1;33m@\033[0m";
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
        std::cout << whereami[i];
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

void paintstart() {
    if(!randomchunk()) return;
    hidecursor();
    //paintchunk();
    paintPlayer();
}