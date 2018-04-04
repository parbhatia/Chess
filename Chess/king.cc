#include "king.h"
#include <iostream>
#include "errors.h"
using namespace std;

bool King::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {  //Assuming newPos is either empty or enemy
	if (((getPos().row == newPos.row - 1) && (getPos().col == newPos.col)) || //down
		((getPos().row == newPos.row - 1) && (getPos().col == newPos.col - 1)) || //down-right
		((getPos().row == newPos.row - 1) && (getPos().col == newPos.col + 1)) || //down-left
		((getPos().row == newPos.row) && (getPos().col == newPos.col - 1)) || //right
		((getPos().row == newPos.row) && (getPos().col == newPos.col + 1)) || //left
		((getPos().row == newPos.row + 1) && (getPos().col == newPos.col)) || //up
		((getPos().row == newPos.row + 1) && (getPos().col == newPos.col - 1)) || //up-right
		((getPos().row == newPos.row + 1) && (getPos().col == newPos.col + 1))) { //up-left
		return true;
	}
    
    if (getMoved() == false) {
		if (getColor() == White) {
			if ((newPos.row == 7) && (newPos.col == 6) &&            //White short-castling e1-g1
				(pieces[newPos.row][newPos.col] == nullptr) &&       //g1 must be empty
				(pieces[newPos.row][newPos.col - 1] == nullptr) &&   //f1 must be empty
				(pieces[newPos.row][newPos.col + 1]->getMoved() == false)) { //right-bottom castle must not moved
				return true;
			} else if ((newPos.row == 7) && (newPos.col == 2) &&     //White long-castling e1-c1
				(pieces[newPos.row][newPos.col] == nullptr) &&       //c1 must be empty
				(pieces[newPos.row][newPos.col - 1] == nullptr) &&   //b1 must be empty
				(pieces[newPos.row][newPos.col + 1] == nullptr) &&   //d1 must be empty
				(pieces[newPos.row][newPos.col - 2]->getMoved() == false)) { //left-bottom castle must not moved
                return true;
			} else {
				return false;
			}
		}
        if (getColor() == Black) {
			if ((newPos.row == 0) && (newPos.col == 6) &&            //Black short-castling e7-g7
				(pieces[newPos.row][newPos.col] == nullptr) &&       //g7 must be empty
				(pieces[newPos.row][newPos.col - 1] == nullptr) &&   //f7 must be empty
				(pieces[newPos.row][newPos.col + 1]->getMoved() == false)) { //right-top castle must not moved
				return true;
			} else if ((newPos.row == 0) && (newPos.col == 2) &&     //Black long-castling e7-c7
				(pieces[newPos.row][newPos.col] == nullptr) &&       //c7 must be empty
				(pieces[newPos.row][newPos.col - 1] == nullptr) &&   //b7 must be empty
				(pieces[newPos.row][newPos.col + 1] == nullptr) &&   //d7 must be empty
				(pieces[newPos.row][newPos.col - 2]->getMoved() == false)) { //left-top castle must not moved
                return true;
			} else {
				return false;
			}
		}
	}
    
    return false;
}


vector<Pos> King::getPossibleMoves(vector <vector<Piece*>> pieces) {
	vector<Pos> vec;

	if ((getPos().row - 1 >= 0) && (getPos().col - 1 >= 0) &&    //moving up-left
		((pieces[getPos().row - 1][getPos().col - 1] == nullptr) || 
			(pieces[getPos().row - 1][getPos().col - 1]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row - 1, getPos().col - 1});
	}

	if ((getPos().row - 1 >= 0) &&                               //moving up
		((pieces[getPos().row - 1][getPos().col] == nullptr) || 
			(pieces[getPos().row - 1][getPos().col]->getColor() != getColor()))) {
		vec.push_back(Pos{getPos().row - 1, getPos().col});
	}

	if ((getPos().row - 1 >= 0) && (getPos().col + 1 <= 7) &&    //moving up-right
		((pieces[getPos().row - 1][getPos().col + 1] == nullptr) || 
			(pieces[getPos().row - 1][getPos().col + 1]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row - 1, getPos().col + 1});
	}

	if ((getPos().col - 1 >= 0) &&                               //moving left
		((pieces[getPos().row][getPos().col - 1] == nullptr) || 
			(pieces[getPos().row][getPos().col - 1]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row, getPos().col - 1});
	}

	if ((getPos().col + 1 <= 7) &&                               //moving right
		((pieces[getPos().row][getPos().col + 1] == nullptr) || 
			(pieces[getPos().row][getPos().col + 1]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row, getPos().col + 1});
	}

	if ((getPos().row + 1 <= 7) && (getPos().col - 1 >= 0) &&    //moving down-left
		((pieces[getPos().row + 1][getPos().col - 1] == nullptr) || 
			(pieces[getPos().row + 1][getPos().col - 1]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row + 1, getPos().col - 1});
	}

	if ((getPos().row + 1 <= 7) &&                               //moving down
		((pieces[getPos().row + 1][getPos().col] == nullptr) || 
			(pieces[getPos().row + 1][getPos().col]->getColor() != getColor()))) {
            vec.push_back(Pos{getPos().row + 1, getPos().col});
	}

	if ((getPos().row + 1 <= 7) && (getPos().col + 1 <= 7) &&    //moving down-right
		((pieces[getPos().row + 1][getPos().col + 1] == nullptr) || 
			(pieces[getPos().row + 1][getPos().col + 1]->getColor() != getColor()))) {
            vec.push_back({getPos().row + 1, getPos().col + 1});
	}
    

    //White long castling
	if((getPos().row == 7) && (getPos().col == 4) && (IsLegal({7, 2}, pieces) == true)) {
        vec.push_back(Pos{7,2});
	} 
    //White short castling
	if((getPos().row == 7) && (getPos().col == 4) && (IsLegal({7, 6}, pieces) == true)) {
        vec.push_back({7,6});
	}
	//Black long castling
	if((getPos().row == 0) && (getPos().col == 4) && (IsLegal({0, 2}, pieces) == true)) {
        vec.push_back({0,2});
	} 
    //White short castling
	if((getPos().row == 0) && (getPos().col == 4) && (IsLegal({0, 6}, pieces) == true)) {
        vec.push_back({0,6});
	}
    
    return vec;
}

King::King(Color c, Pos pos, bool hasMoved) : Piece{c,pos} {}

void King::print(std::ostream& out) const {
    if (getColor() == White) out << 'K';
    else out << 'k';
}

