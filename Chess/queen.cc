#include "queen.h"
#include <cmath>
#include "errors.h"
#include <iostream>
using namespace std;

bool Queen::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {  //Assuming newPos is either empty or enemy
    int arow = abs(newPos.row - getPos().row);
    int acol = abs(newPos.col - getPos().col);
    
    if (arow == acol) {
        if(getPos().row < newPos.row) {
            if(getPos().col < newPos.col) {   //moving right-bottom
                for(int i = getPos().row + 1, y = getPos().col + 1; (i < newPos.row) && (y < newPos.col); ++i, ++y) {
                    if(pieces[i][y] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else if(getPos().col > newPos.col) {   //moving left-bottoms
                for(int i = getPos().row + 1, y = getPos().col - 1; (i < newPos.row) && (y > newPos.col); ++i, --y) {
                    if(pieces[i][y] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else if(getPos().row > newPos.row) {
            if(getPos().col < newPos.col) {   //moving right-top
                for(int i = getPos().row - 1, y = getPos().col + 1; (i > newPos.row) && (y < newPos.col); --i, ++y) {
                    if(pieces[i][y] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else if(getPos().col > newPos.col) {   //moving left-top
                for(int i = getPos().row - 1, y = getPos().col - 1; (i > newPos.row) && (y > newPos.col); --i, --y) {
                    if(pieces[i][y] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else if(getPos().row == newPos.row) {    //moving horizontally
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
        } else {
            return false;
        }
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
        } else {
            return false;
        }
    } else {
        return false;
    }
}

vector<Pos> Queen::getPossibleMoves(vector<vector<Piece*>> pieces) { //We need to check destination cell if it's empty or enemy
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
           (IsLegal({i, getPos().col}, pieces) == true)) {
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
    
    for(int i = getPos().row + 1, y = getPos().col + 1; (i <= 7) && (y <= 7); ++i, ++y) { //check right-bottom
        if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, y}, pieces) == true)) {
            vec.push_back(Pos{i,y});
        } else {
            break;
        }
    }
    
    for(int i = getPos().row + 1, y = getPos().col - 1; (i <= 7) && (y >= 0); ++i, --y) { //check left-bottom
        if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, y}, pieces) == true)) {
            vec.push_back(Pos{i,y});
        } else {
            break;
        }
    }
    
    for(int i = getPos().row - 1, y = getPos().col + 1; (i >= 0) && (y <= 7); --i, ++y) { //check right-top
        if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, y}, pieces) == true)) {
            vec.push_back(Pos{i,y});
        } else {
            break;
        }
    }
    
    for(int i = getPos().row - 1, y = getPos().col - 1; (i >= 0) && (y >= 0); --i, --y) { //check left-top
        if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
           (IsLegal({i, y}, pieces) == true)) {
            vec.push_back(Pos{i,y});
        } else {
            break;
        }
    }
    
    return vec;
}

Queen::Queen(Color c, Pos pos, bool hasMoved, int priority): Piece{c, pos, hasMoved, priority} {}


void Queen::print(std::ostream& out) const {
    if (getColor() == White) out << 'Q';
    else out << 'q';
}

Queen::~Queen() {}
