// Loads pacman map from a textfile
// Pacman game


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include windows.h
using namespace std;



BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}


struct Packman {
    char look;
    int xpos = 1;
    int ypos = 1;
    int foodCount = 0;
    
    Packman(char a) {
        look = a;
    }
    
};

/*************************************************************************/

bool loadFile(vector <string> & vec, int & foodCounter) {
    ifstream loadFile;
    string fileName, input;
    bool loadOK = false;
    do {
        cout << "Please enter the name of the file" << endl;
        getline(cin, fileName);
        loadFile.open(fileName);
        loadOK = false;
        if (loadFile) {
            loadOK = true;
            while (getline(loadFile, input)) {
                vec.push_back(input);
            }
            
            if (!vec.empty()) {
                for (int i = 0; i < vec.size(); i++) {
                    for (int j = 0; j < vec.at(i).size(); j++) {
                        foodCounter += (toupper(vec.at(i).at(j)) == 'X');
                    }
                }
            }
            else cout << "empty vector" << endl;
        }
        else cout << "The file could not be loaded please try again" << endl;
        
        loadFile.close();
    } while (vec.empty() || !loadOK);
    return vec.empty() + !loadOK;
}

bool moveIt(vector <string> & map, int xPos, int yPos, Packman & pac) {
    
    int returnvalue = 0;
    if (toupper(map.at(pac.ypos+yPos).at(pac.xpos+xPos)) == 'X') {
        pac.foodCount++;
    }
    
    if (pac.xpos + xPos < map.at(0).size() && pac.ypos + yPos < map.size()) {
        
        map.at(pac.ypos).at(pac.xpos) = ' ';
        pac.xpos += xPos;
        pac.ypos += yPos;
        
        map.at(pac.ypos).at(pac.xpos) = pac.look;
        
        returnvalue++;
    }
    
    return returnvalue;
}


void displayMap(vector<string> & map) {
    for (int i = 0; i < map.size(); i++) {
        cout << map.at(i) << endl;
    }
}


int main()
{
    
    int foodCounter = 0;
    
    Packman pac1('@'), pac2('$');
    vector<string>map;
    bool game_running = true;
    
    loadFile(map, foodCounter);
    do {
        gotoxy(0, 0);
        
        displayMap(map);
        cout <<"A pacman @ ate: "<< pac1.foodCount << endl;
        cout <<"A pacman $ ate: "<< pac2.foodCount << endl;
        system("pause>nul");
        
        if (GetAsyncKeyState(VK_DOWN) && moveIt(map, 0, 1, pac1)) {
            
        }
        
        
        if (GetAsyncKeyState(VK_UP) && moveIt(map, 0, -1, pac1)) {
            
            
        }
        
        if (GetAsyncKeyState(VK_RIGHT) && moveIt(map, 1, 0, pac1)) {
            
            
        }
        
        if (GetAsyncKeyState(VK_LEFT) && moveIt(map, -1, 0, pac1)) {
            
        }
        if (GetAsyncKeyState(0x53) && moveIt(map, 0, 1, pac2)) {
            
        }
        if (GetAsyncKeyState(0x57) && moveIt(map, 0, -1, pac2)) {
            
        }
        if (GetAsyncKeyState(0x44) && moveIt(map, 1, 0, pac2)) {
            
        }
        if (GetAsyncKeyState(0x41) && moveIt(map, -1, 0, pac2)) {
            
        }
        
        
        if (GetAsyncKeyState(VK_ESCAPE) || pac1.foodCount+pac2.foodCount == foodCounter) {
            game_running = false;
        }
        
        
    } while (game_running == true);
    
    system("cls");
    cout << "GAME OVER" << endl;
    cout << ((pac1.foodCount > pac2.foodCount) ? "Won 1st Pacman" : "Won 2nd Pacman") << endl;
    return 0;
    
}
