#include "bishop.h"
#include <cmath>
using namespace std;

bool Bishop::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {  //Assuming newPos is either empty or enemy
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
      } else if(getPos().col > newPos.col) {   //moving left-bottom
        for(int i = getPos().row + 1, y = getPos().col - 1; (i < newPos.row) && (y > newPos.col); ++i, --y) {
          if(pieces[i][y] != nullptr) {
            return false;
          }
        }
        return true;
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
      }
    }
  } else {
    return false;
  }
}


vector<Pos> Bishop::getPossibleMoves(vector <vector<Piece*>> pieces) {  //We need to check destination cell if it's empty or enemy
  vector<Pos> vec;
  
  for(int i = getPos().row + 1, y = getPos().col + 1; (i <= 7) && (y <= 7); ++i, ++y) { //check right-bottom
    if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
       (IsLegal({i, y}, pieces) == true)) {
      vec.push_back = {i,y};
    } else {
      break;
    }
  }
  
  for(int i = getPos().row + 1, y = getPos().col - 1; (i <= 7) && (y >= 0); ++i, --y) { //check left-bottom
    if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
       (IsLegal({i, y}, pieces) == true)) {
      vec.push_back = {i,y};
    } else {
      break;
    }
  }
  
  for(int i = getPos().row - 1, y = getPos().col + 1; (i >= 0) && (y <= 7); --i, ++y) { //check right-top
    if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
       (IsLegal({i, y}, pieces) == true)) {
      vec.push_back = {i,y};
    } else {
      break;
    }
  }
  
  for(int i = getPos().row - 1, y = getPos().col - 1; (i >= 0) && (y >= 0); --i, --y) { //check left-top
    if(((pieces[i][y] == nullptr) || (pieces[i][y]->getColor() != getColor())) &&  //destionation cell condition
       (IsLegal({i, y}, pieces) == true)) {
      vec.push_back = {i,y};
    } else {
      break;
    }
  }
  
  return vec;
}

Bishop::Bishop(Color c, Pos Pos, bool hasMoved = false): Piece(c , Pos) {}
