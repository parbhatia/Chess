#include "textdisplay.h"
#include <iostream>
#include <string>
#include <vector>
#include "board.h"
using namespace std;

class Piece;

TextDisplay::TextDisplay() { // clears old board and sets up new 10x10 display
    if (theDisplay.size() > 0) theDisplay.clear(); //clear old board
    //create empty display
    for(int i=0; i<10; ++i) {
        vector<char> V;
        for (int j=0; j<10; ++j) {
            V.emplace_back(' ');
        }
        theDisplay.emplace_back(V);
    }
    //add column characters
    theDisplay[0][0] = '8';
    theDisplay[1][0] = '7';
    theDisplay[2][0] = '6';
    theDisplay[3][0] = '5';
    theDisplay[4][0] = '4';
    theDisplay[5][0] = '3';
    theDisplay[6][0] = '2';
    theDisplay[7][0] = '1';
    //add row characters
    theDisplay[9][2] = 'a';
    theDisplay[9][3] = 'b';
    theDisplay[9][4] = 'c';
    theDisplay[9][5] = 'd';
    theDisplay[9][6] = 'e';
    theDisplay[9][7] = 'f';
    theDisplay[9][8] = 'g';
    theDisplay[9][9] = 'h';
}

/*
    //tile colours
    for(int i=0; i<8; ++i) {
        for(int j=2; j<10; ++j) {
            if ((i+j)%2 != 0) { //if black tiles
                theDisplay[i][j] = '_';
            }
        }
    }
}


void TextDisplay::insert (Pos pos, char letter) {
    int r = pos.row;
    int c = pos.col + 2; //must increment column pos by 2
    theDisplay[r][c] = letter;
}

void TextDisplay::remove (Pos pos) {
    int r = pos.row;
    int c = pos.col + 2; //must increment column pos by 2
    if ((r+c)%2 != 0) { //black tile
        theDisplay[r][c] = '_';
    } else {
        theDisplay[r][c] = ' ';
    }
}
 
*/

ostream& operator<<(ostream &os, const TextDisplay &td) {
    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {
            if((i>=2 && i<10) && (j>=0 && j<8)) {
                if (getPieces()[i][j] != NULL) {
                    os << getPieces()[i][j];
                }
            } else { //will print alphabet and row indeces
                
            }
            os << td.theDisplay[i][j];
        }
        os << endl;
    }
    return os;
}
