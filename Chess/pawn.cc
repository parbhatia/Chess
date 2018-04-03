#include "pawn.h"
using namespace std;

bool Pawn::getPassant() {
  return enPassant;
}

void Pawn::setPassant(bool val) {
  enPassant = val;
}

bool Pawn::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {
  if(getColor() == Black) {
    if(((getPos().col == newPos.col) && (getPos().row == (newPos.row - 1)) && (pieces[newPos.row][newPos.col] == nullptr)) ||  //1 forward
       ((getMoved() == false) && (getPos().col == newPos.col) && (getPos().row == (newPos.row - 2)) &&   //2 forward 
        (pieces[newPos.row][newPos.col] == nullptr) && (pieces[newPos.row - 1][newPos.col] == nullptr)) ||
       (((getPos().col == (newPos.col + 1)) || (getPos().col == (newPos.col - 1))) && (getPos().row == (newPos.row - 1)) &&   //1 diagnol move
        (pieces[newPos.row][newPos.col] != nullptr) && (pieces[newPos.row][newPos.col]->getColor() == White)) ||  //regular attack
        ((pieces[newPos.row][newPos.col] == nullptr) && (pieces[newPos.row - 1][newPos.col] != nullptr) &&  //enPassant
         (pieces[newPos.row - 1][newPos.col]->getColor() == White) && (pieces[newPos.row - 1][newPos.col]->getPassant() == true) &&
         (getPassant() == true))) {
      return true;
    } else {
      return false;
    }
  }
    
  if (getColor() == White) {
      if(((getPos().col == newPos.col) && (getPos().row == (newPos.row + 1)) && (pieces[newPos.row][newPos.col] == nullptr)) ||  //1 forward
        ((getMoved() == false) && (getPos().col == newPos.col) && (getPos().row == (newPos.row + 2)) &&   //2 forward
        (pieces[newPos.row][newPos.col] == nullptr) && (pieces[newPos.row + 1][newPos.col] == nullptr)) ||
        (((getPos().col == (newPos.col + 1)) || (getPos().col == (newPos.col - 1))) && (getPos().row == (newPos.row + 1)) &&   //1 diagnol
        (pieces[newPos.row][newPos.col] != nullptr) && (pieces[newPos.row][newPos.col]->getColor() == Black)) ||  //regular attack
        ((pieces[newPos.row][newPos.col] == nullptr) && (pieces[newPos.row + 1][newPos.col] != nullptr) &&  //enPassant
        (pieces[newPos.row + 1][newPos.col]->getColor() == Black) && (pieces[newPos.row + 1][newPos.col]->getPassant() == true) &&
        (getPassant() == true))) {
            return true;
            
        } else {
            return false;
        }
  }
    return false;
}

      
       
vector<Pos> Pawn::getPossibleMoves(vector<vector<Piece*>> pieces) {
  vector<Pos> vec;
  
  if(getColor() == Black) {
    if(IsLegal({getPos().row + 1, getPos().col}, pieces) == true) {  //1 forward
        vec.push_back(Pos{getPos().row + 1, getPos().col});
    }
    if(IsLegal({getPos().row + 2, getPos().col}, pieces) == true) {  //2 forward
        vec.push_back(Pos {getPos().row + 2, getPos().col});
    } 
    if((getPos().col + 1 <= 7) && (IsLegal({getPos().row + 1, getPos().col + 1}, pieces) == true)) {  //1 diagnol right
        vec.push_back(Pos{getPos().row + 1, getPos().col + 1});
    }
    if((getPos().col - 1 >= 0) && (IsLegal({getPos().row + 1, getPos().col - 1}, pieces) == true)) {  //1 diagnol left
        vec.push_back(Pos{getPos().row + 1, getPos().col - 1});
    }
  } else if(getColor() == White) {
    if(IsLegal({getPos().row - 1, getPos().col}, pieces) == true) {  //1 forward
        vec.push_back(Pos{getPos().row - 1, getPos().col});
    }
    if(IsLegal({getPos().row - 2, getPos().col}, pieces) == true) {  //2 forward
        vec.push_back(Pos{getPos().row - 2, getPos().col});
    }
    if((getPos().col + 1 <= 7) && (IsLegal({getPos().row - 1, getPos().col + 1}, pieces) == true)) {  //1 diagnol right
        vec.push_back(Pos{getPos().row - 1, getPos().col + 1});
    }
    if((getPos().col - 1 >= 0) && (IsLegal({getPos().row - 1, getPos().col - 1}, pieces) == true)) {  //1 diagnol left
        vec.push_back(Pos{getPos().row - 1, getPos().col - 1});
    }
  }
  
  return vec;
}

Pawn::Pawn(Color c, Pos pos, bool hasMoved = false, bool enPassant = false): Piece{c ,pos, hasMoved}, enPassant{enPassant} {}
