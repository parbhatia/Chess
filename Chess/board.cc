#include "board.h"
#include <iostream>
#include <string>
#include <vector>
#include "move.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "errors.h"
#include <cmath>
#include <sstream>
using namespace std;

vector<Move*> Board::getMoves() {
    return moves;
}

Pos Board::enemyKingPos(Color color) {
    if (color == White) return bk->getPos();
    else return wk->getPos();
}

void Board::setCount(char c, int i) {
    if (c == '-') count = count - i;
    else count = count + i;
}

int Board::getCount() const {
    return count;
}

void Board::insert (Pos pos, char letter) {
    int r = pos.row;
    int c = pos.col;
    if (letter == 'R') { pieces[r][c] = new Rook(White,pos); }
    else if (letter == 'N') { pieces[r][c] = new Knight(White,pos); }
    else if (letter == 'B') { pieces[r][c] = new Bishop(White,pos); }
    else if (letter == 'Q') { pieces[r][c] = new Queen(White,pos); }
    else if (letter == 'K') { pieces[r][c] = new King(White,pos); }
    else if (letter == 'P') { pieces[r][c] = new Pawn(White,pos); }
    else if (letter == 'r') { pieces[r][c] = new Rook(Black,pos); }
    else if (letter == 'n') { pieces[r][c] = new Knight(Black,pos); }
    else if (letter == 'b') { pieces[r][c] = new Bishop(Black,pos); }
    else if (letter == 'q') { pieces[r][c] = new Queen(Black,pos); }
    else if (letter == 'k') { pieces[r][c] = new King(Black,pos); }
    else { pieces[r][c] = new Pawn(Black,pos); } //letter is 'p'
}

void Board::insert (Piece *p) {
    pieces[p->getPos().row][p->getPos().col] = p;
}

void Board::remove (Pos pos) {
    pieces[pos.row][pos.col] = NULL;
}
vector<vector<Piece*>> Board::getPieces() const { return pieces; }

Board::Board() : count{0} { //sets up new 8x8 board
    for(int i=0; i<8; ++i) {
        vector<Piece*> P;
        for (int j=0; j<8; ++j) {
            P.push_back(NULL);
        }
        pieces.emplace_back(P);
    }
}

ostream& operator<<(ostream &os, const Board &b) {
    //store column and row indices
    std::vector<std::vector<char>> theDisplay;
    for(int i=0; i<10; ++i) {
        vector<char> V;
        for (int j=0; j<10; ++j) {
            V.push_back(' ');
        }
        theDisplay.push_back(V);
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
    //add tile colours
    for(int i=0; i<8; ++i) {
        for(int j=2; j<10; ++j) {
            if ((i+j)%2 != 0) { //if black tiles
                theDisplay[i][j] = '_';
            }
        }
    }
    for (int i=0; i<8; ++i) {
        for (int j=2; j<10; ++j) {
            if (b.getPieces()[i][j-2] != nullptr) {
                stringstream ss;
                char c;
                ss << *(b.getPieces()[i][j-2]);
                ss >> c;
                theDisplay[i][j] = c;
            }
        }
    }
    
    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {
            os << theDisplay[i][j];
        }
        os << endl;
    }
    /////////////////////////
    return os;
}

void Board::makeTheMove(Pos mPos, Pos tPos, char prm){
    bool RegularMove = true;
    
    //Promotion Condition
    if((pieces[mPos.row][mPos.col]->isPawn() == true) &&
       ((tPos.row == 7) || (tPos.row == 0))) {
        RegularMove = false;
        Piece* promotionPiece = NULL;
        if(tPos.row == 7) {
            if(prm == 'r') {
                promotionPiece = new Rook(Black, {tPos.row, tPos.col}, true);
            } else if (prm == 'b') {
                promotionPiece = new Bishop(Black, {tPos.row, tPos.col}, true);
            } else if (prm == 'n') {
                promotionPiece = new Knight(Black, {tPos.row, tPos.col}, true);
            } else {
                promotionPiece = new Queen(Black, {tPos.row, tPos.col}, true);
            }
        } else if(tPos.row == 0) {
            if(prm == 'R') {
                promotionPiece = new Rook(White, {tPos.row, tPos.col}, true);
            } else if (prm == 'B') {
                promotionPiece = new Bishop(White, {tPos.row, tPos.col}, true);
            } else if (prm == 'N') {
                promotionPiece = new Knight(White, {tPos.row, tPos.col}, true);
            } else {
                promotionPiece = new Queen(White, {tPos.row, tPos.col}, true);
            }
        }
        
        
        pieces[tPos.row][tPos.col] = promotionPiece;
        pieces[mPos.row][mPos.col] = nullptr;
        Move *m = new Move{mPos, tPos, nullptr, "Promotion"};
        moves.emplace_back(m);
    }
    
    
    //possible enPassant capture:
    if (((mPos.row == 3 && tPos.row == 2) || (mPos.row == 4 && tPos.row == 5)) &&
        (abs(mPos.col - tPos.col) == 1) &&
        (pieces[mPos.row][mPos.col] != nullptr) &&
        (pieces[tPos.row][tPos.col] == nullptr) &&
        (pieces[mPos.row][mPos.col]->isPawn() == true)) {
        RegularMove = false;
        Move *m = new Move{mPos, tPos, pieces[mPos.row][tPos.col], "enPassantCapture"};
        moves.emplace_back(m);
        pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col]; //capturing pawn moves to target
        pieces[tPos.row][tPos.col]->updatePos(tPos); //Update Position of the piece
        pieces[mPos.row][mPos.col] = nullptr; //old position of the capturing pawn
        pieces[mPos.row][tPos.col] = nullptr; //position of the captured pawn
    }
    
    
    if ((moves.empty() == false) && (moves.back()->specialMove == "enPassantCapture")) {
        //Setting enPassant field of the pieces to false after enPassantCapture
        //We don't set enPassant field of captured piece to false
        pieces[moves.back()->newPos.row][moves.back()->newPos.col]->setPassant(false);
        if ((moves.back()->newPos.col + 1 == moves.back()->oldPos.col) &&
            (moves.back()->oldPos.col - 2 >= 0)) {
            if(pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2] != nullptr) {
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2]->setPassant(false);
            }
        }
        if ((moves.back()->newPos.col - 1 == moves.back()->oldPos.col) &&
            (moves.back()->oldPos.col + 2 <= 7)) {
            if(pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2] != nullptr) {
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2]->setPassant(false);
            }
        }
    }
    
    if ((moves.empty() == false) && (moves.back()->specialMove == "enPassantSetup")) {
        //if the next move is not enPassant we set all enPassant fields to false before
        //the other conditions
        pieces[moves.back()->newPos.row][moves.back()->newPos.col]->setPassant(false);
        if(!outOfRange({moves.back()->newPos.row, moves.back()->newPos.col + 1}) && (pieces[moves.back()->newPos.row][moves.back()->newPos.col + 1] != nullptr)) {
            pieces[moves.back()->newPos.row][moves.back()->newPos.col + 1]->setPassant(false);
        }
        if(!outOfRange({moves.back()->newPos.row, moves.back()->newPos.col - 1}) &&
           pieces[moves.back()->newPos.row][moves.back()->newPos.col - 1] != nullptr) {
            pieces[moves.back()->newPos.row][moves.back()->newPos.col - 1]->setPassant(false);
        }
    }
    
    
    if ((pieces[mPos.row][mPos.col] != nullptr) &&
        (pieces[mPos.row][mPos.col]->isPawn() == true) && //possible enPassant setup (2 forward move)
        ((mPos.row == 1 && tPos.row == 3) || (mPos.row == 6 && tPos.row == 4))) {
        RegularMove = false;
        Move *m = new Move{mPos, tPos, nullptr, "enPassantSetup"};
        moves.emplace_back(m);
        pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col]; //2 forward
        pieces[tPos.row][tPos.col]->updatePos(tPos);
        pieces[mPos.row][mPos.col] = nullptr;
        /*pieces[mPos.row][mPos.col]->setPassant(true);
        if(!(outOfRange({mPos.row, mPos.col + 1})) &&
           (pieces[mPos.row][mPos.col + 1] != nullptr)) {
            pieces[mPos.row][mPos.col + 1]->setPassant(true);
        }
        if(!(outOfRange({mPos.row, mPos.col - 1})) &&
           (pieces[mPos.row][mPos.col - 1] != nullptr)) {
            pieces[mPos.row][mPos.col - 1]->setPassant(true);
        }*/
    }
    
    
    if ((pieces[mPos.row][mPos.col] != nullptr) &&
        (pieces[mPos.row][mPos.col]->getMoved() == false) &&   //short-castling condition for both colors
        ((mPos.row == 0) || (mPos.row == 7)) && (mPos.col == 4) &&
        (tPos.col == 6)) {
        RegularMove = false;
        Move *m = new Move{mPos, tPos, nullptr, "Castling"};
        moves.emplace_back(m);
        pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col];
        pieces[tPos.row][tPos.col]->updatePos(tPos);
        pieces[mPos.row][mPos.col] = nullptr;
        pieces[tPos.row][tPos.col]->setMoved(true);
        pieces[mPos.row][5] = pieces[mPos.row][7]; //moves the castle to the new loc
        pieces[mPos.row][5]->updatePos({mPos.row, 5});
        pieces[mPos.row][7] = nullptr;
        pieces[mPos.row][5]->setMoved(true);
        if (isAttacked({mPos.row, 5}) == true) {
            undo();
            throw castling_fail();
        }

        
    }
    
    if ((pieces[mPos.row][mPos.col] != nullptr) &&
        (pieces[mPos.row][mPos.col]->getMoved() == false) &&   //long-castling condition for both colors
        ((mPos.row == 0) || (mPos.row == 7)) && (mPos.col == 4) &&
        (tPos.col == 2)) {
        RegularMove = false;
        Move *m = new Move{mPos, tPos, nullptr, "Castling"};
        moves.emplace_back(m);
        pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col];
        pieces[tPos.row][tPos.col]->updatePos(tPos);
        pieces[mPos.row][mPos.col] = nullptr;
        pieces[tPos.row][tPos.col]->setMoved(true);
        pieces[mPos.row][3] = pieces[mPos.row][0]; //moves the castle to the new loc
        pieces[mPos.row][3]->updatePos({mPos.row, 3});
        pieces[mPos.row][0] = nullptr;
        pieces[mPos.row][3]->setMoved(true);
        if (isAttacked({mPos.row, 3}) == true) {
            undo();
            throw castling_fail();
        }
    }
    
    if(RegularMove == true) {
        if(pieces[mPos.row][mPos.col]->getMoved() == false) {
            Move* m = new Move{mPos, tPos, pieces[tPos.row][tPos.col], "FirstMove"};
            moves.emplace_back(m); //info about move is pushed to moved vec in board
            pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col]; //target cell points to moved piece
            pieces[tPos.row][tPos.col]->setMoved(true);
            pieces[tPos.row][tPos.col]->updatePos(tPos);
            pieces[mPos.row][mPos.col] = nullptr; //freeing old cell
        } else {
            Move* m = new Move{mPos, tPos, pieces[tPos.row][tPos.col], "Regular"};
            moves.emplace_back(m); //info about move is pushed to moved vec in board
            pieces[tPos.row][tPos.col] = pieces[mPos.row][mPos.col]; //target cell points to moved piece
            pieces[tPos.row][tPos.col]->setMoved(true);
            pieces[tPos.row][tPos.col]->updatePos(tPos);
            pieces[mPos.row][mPos.col] = nullptr; //freeing old cell
        }
    }
}


void Board::undo() {
    if(moves.empty() == false) {
        if(moves.back()->specialMove == "enPassantCapture") {
            pieces[moves.back()->oldPos.row][moves.back()->newPos.col] = moves.back()->captured; //Put the captured piece back
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col]; //Put the attacker pawn back
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
            pieces[moves.back()->newPos.row][moves.back()->newPos.col] = nullptr;
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setPassant(true);
            if ((moves.back()->newPos.col + 1 == moves.back()->oldPos.col) &&
                (moves.back()->oldPos.col - 2 >= 0) &&
                (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2] != nullptr) &&
                (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2]->getColor() ==
                (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->getColor()))) {
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2]->setPassant(true);
            }
            if ((moves.back()->newPos.col - 1 == moves.back()->oldPos.col) &&
                (moves.back()->oldPos.col + 2 <= 7) &&
                (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2] != nullptr) &&
                (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2]->getColor() ==
                 (pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->getColor()))) {
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2]->setPassant(true);
            }
            moves.pop_back();
            return;
        }
        if(moves.back()->specialMove == "enPassantSetup") {
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col]; //Put the 2 forward pawn back
            pieces[moves.back()->newPos.row][moves.back()->newPos.col] = nullptr;
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setPassant(false);
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setMoved(false);
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
            if(!outOfRange({moves.back()->newPos.row, moves.back()->newPos.col + 1}) &&
               pieces[moves.back()->newPos.row][moves.back()->newPos.col + 1] != nullptr) {
                pieces[moves.back()->newPos.row][moves.back()->newPos.col + 1]->setPassant(false);
            }
            if(!outOfRange({moves.back()->newPos.row, moves.back()->newPos.col - 1}) && pieces[moves.back()->newPos.row][moves.back()->newPos.col - 1] != nullptr) {
                pieces[moves.back()->newPos.row][moves.back()->newPos.col - 1]->setPassant(false);
            }
            moves.pop_back();
            return;
        }
        if(moves.back()->specialMove == "Castling") {
            if(moves.back()->newPos.col == 2) { //long castling
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col]; //Put king back
                pieces[moves.back()->newPos.row][moves.back()->newPos.col] = nullptr;
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setMoved(false);
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
                pieces[moves.back()->newPos.row][0] = pieces[moves.back()->newPos.row][3];
                pieces[moves.back()->newPos.row][3] = nullptr;
                (pieces[moves.back()->newPos.row][0])->setMoved(false);
                pieces[moves.back()->oldPos.row][0]->updatePos({moves.back()->oldPos.row, 0});
                moves.pop_back();
            } else if (moves.back()->newPos.col == 6) { //short castling
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col]; //Put king back
                pieces[moves.back()->newPos.row][moves.back()->newPos.col] = nullptr;
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setMoved(false);
                pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
                pieces[moves.back()->newPos.row][7] = pieces[moves.back()->newPos.row][5];
                pieces[moves.back()->newPos.row][5] = nullptr;
                pieces[moves.back()->newPos.row][7]->setMoved(false);
                pieces[moves.back()->oldPos.row][7]->updatePos({moves.back()->oldPos.row, 7});
                moves.pop_back();
            }
            return;
        }
        if(moves.back()->specialMove == "Promotion") {
            Color c;
            if(moves.back()->newPos.row == 7) {
                c = Black;
            } else {
                c = White;
            }
            pieces[moves.back()->newPos.row][moves.back()->newPos.col] = nullptr;
            Piece* promotionPiece = new Pawn(c, moves.back()->oldPos, true);
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = promotionPiece;
            moves.pop_back();
            return;
        }
        
        if(moves.back()->specialMove == "Regular") {
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col];
            pieces[moves.back()->newPos.row][moves.back()->newPos.col] = moves.back()->captured;
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
            moves.pop_back();
            return;
        }
        
        if(moves.back()->specialMove == "FirstMove") {
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col] = pieces[moves.back()->newPos.row][moves.back()->newPos.col];
            pieces[moves.back()->newPos.row][moves.back()->newPos.col] = moves.back()->captured;
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->updatePos(moves.back()->oldPos);
            pieces[moves.back()->oldPos.row][moves.back()->oldPos.col]->setMoved(false);
            moves.pop_back();
            return;
        }
    }
}

bool Board::outOfRange(const Pos p) const {
    if ((p.row <= 7) && (p.row >= 0) &&
        (p.col <= 7) && (p.col >= 0)) {
        return false;
    }
    return true;
}

bool Board::isAttacked(Pos cellPos) {
    Piece* piece = pieces[cellPos.row][cellPos.col];
    for(int i=0; i<8; ++i) {
        for(int y=0; y<8; ++y) {
            //skipping owned pieces and empty cells:
            if(pieces[i][y] == nullptr) continue;
            if((piece !=  nullptr)&&
               (piece->getColor() == pieces[i][y]->getColor())) continue;
            //checking if p can move to curPos
            if (pieces[i][y]->IsLegal(cellPos, pieces)){
                return true;
            }
            
        }
    }
    return false; //has checked all enemy pieces and none of them attacks player's king
}

Board::~Board() {
    for(auto &row: pieces) {
        for(auto &p: row) {
            delete p;
        }
    }
    for(auto &k: moves) {
        delete k;
    }
}

