#include "rook.h"
#include "errors.h"
#include <iostream>
using namespace std;

bool Rook::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {  //Assuming newPos is either empty or enemy

    if(getPos().row == newPos.row) {    //moving horizontally
        if(getPos().col < newPos.col) {   //to right
            for(int i = getPos().col + 1; i < newPos.col; ++i) {
                if(pieces[getPos().row][i] != nullptr) {
                    return false;
                }
            }
            return true;
        } else if(getPos().col > newPos.col) {  //to left
            for(int i = getPos().col - 1; i > newPos.col; --i) {
                if(pieces[getPos().row][i] != nullptr) {
                    return false;
                }
            }
            return true;
        }
        return false;
    } else if(getPos().col == newPos.col) { //moving vertically
        if(getPos().row < newPos.row) {   //to down
            for(int i = getPos().row + 1; i < newPos.row; ++i) {
                if(pieces[i][getPos().col] != nullptr) {
                    return false;
                }
            }
            return true;
        } else if(getPos().row > newPos.row) {   //to up
            for(int i = getPos().row - 1; i > newPos.row; --i) {
                if(pieces[i][getPos().col] != nullptr) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    return false;
}

vector<Pos> Rook::getPossibleMoves(vector <vector<Piece*>> pieces) {  //We need to check destination cell if it's empty or enemy
    vector<Pos> vec;
    
    for(int i = getPos().col + 1; i <= 7; ++i) { //check right
        if(((pieces[getPos().row][i] == nullptr) || (pieces[getPos().row][i]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({getPos().row, i}, pieces) == true)) {
            vec.push_back(Pos{i,getPos().col});
        } else {
            break;
        }
    }
    
    for(int i = getPos().col - 1; i >= 0; --i) { //check left
        if(((pieces[getPos().row][i] == nullptr) || (pieces[getPos().row][i]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({getPos().row, i}, pieces) == true)) {
            vec.push_back(Pos{i,getPos().col});
        } else {
            break;
        }
    }
    
    for(int i = getPos().row + 1; i <= 7; ++i) { //check bottom
        if(((pieces[i][getPos().col] == nullptr) || (pieces[i][getPos().col]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, getPos().col},  pieces) == true)) {
            vec.push_back(Pos{i, getPos().col});
        } else {
            break;
        }
    }
    
    for(int i = getPos().row - 1; i >= 0; --i) { //check top
        if(((pieces[i][getPos().col] == nullptr) || (pieces[i][getPos().col]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, getPos().col}, pieces) == true)) {
            vec.push_back(Pos{i, getPos().col});
        } else {
            break;
        }
    }
    
    return vec;
}

Rook::Rook(Color c, Pos pos, bool hasMoved): Piece{c, pos, hasMoved} {}

void Rook::print(std::ostream& out) const {
    if (getColor() == White) out << 'R';
    else out << 'r';
}

Rook::~Rook() {}
