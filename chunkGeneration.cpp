#include "common.hpp"
#include "tiles.hpp"

// -- BackoundRarity --
#define BACKGROUND_RARITY 1000
// -- ObjectRarity --
#define OBJECT_RARITY 15000

std::vector<tile> chunk;

// -- get individual char ready --

tile randomfloorchar() {                                //_-|\\/#&$^&*
    int result = genrandomNum(BACKGROUND_RARITY);
    //std::cout << result << " ";

    if (result < 994) {
        return {"\033[2;90m \033[0m", false};
    }
    if (result >= 994 && result < 998) {
        return {"\033[2;90m.\033[0m", false};
    }
    if (result >= 998) {
        return {"\033[2;90m,\033[0m", false};
    }
    return {"\0", false};
}

tile paintObject(int input) {                                //_-|\\/#
    //std::cout << result << " ";

    if (input >= 14900) {
        //return {"\033[90m#\033[0m", true};
        tile temp;
        asteroid::tinyasteroid* tin = new asteroid::tinyasteroid();
        tin->Onspawn(temp);
        objects* obj = static_cast<objects*>(temp.Otherproperties);
        temp.Otherproperties = tin;
        return temp;
    }    return {"\0", true};
}

// -- paint objects onto chunk

void paintObjects() {
    int incr = 0;
    for (int i = 0; i < MAX_DRAW_Y; i++) {
        for (int a = 0; a < MAX_DRAW_X; a++) {
                int Numresult = genrandomNum(OBJECT_RARITY);
                tile result = paintObject(Numresult);
                if (result.display != "\0") {
                    chunk[incr + a] = result;
                }  
        }
        incr += MAX_DRAW_X;
    }
    /*int objectcount = 0;
    for (int i = 0; i < chunk.size(); i++) {
        if (chunk[i].Otherproperties != nullptr) {
            objectcount++;
            std::cout << "object at chunk[" << i << "]\n";
        }
    }
    std::cout << "total objects: " << objectcount << "\n";
    std::cin.get(); // pause so you can read it */
}

// --generate single chunk--

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
    chunk.push_back(randomfloorchar());         // FOR THE EXTRA BIT
    paintObjects();
    return true;
}