#include "knight.h"
#include <iostream>
#include "errors.h"
using namespace std;

bool Knight::IsLegal(Pos newPos, vector <vector<Piece*>> pieces) {  //Assuming newPos is either empty or enemy
	if (((getPos().row == newPos.row + 2) && (getPos().col == newPos.col + 1)) ||  //moving 2 up - 1 left
		((getPos().row == newPos.row + 1) && (getPos().col == newPos.col + 2)) ||  //moving 1 up - 2 left
		((getPos().row == newPos.row + 2) && (getPos().col == newPos.col - 1)) ||  //moving 2 up - 1 right
		((getPos().row == newPos.row + 1) && (getPos().col == newPos.col - 2)) ||  //moving 1 up - 2 right
		((getPos().row == newPos.row - 2) && (getPos().col == newPos.col + 1)) ||  //moving 2 down - 1 left
		((getPos().row == newPos.row - 1) && (getPos().col == newPos.col + 2)) ||  //moving 1 down - 2 left
		((getPos().row == newPos.row - 2) && (getPos().col == newPos.col - 1)) ||  //moving 2 down - 1 right
		((getPos().row == newPos.row - 1) && (getPos().col == newPos.col - 2))) {  //moving 1 down - 2 right
		return true;
	} else {
		return false;
	}
}

vector<Pos> Knight::getPossibleMoves(vector <vector<Piece*>> pieces) {
	vector<Pos> vec;

	if ((getPos().row - 2 >= 0) && (getPos().col - 1 >= 0) &&    //moving 2 up - 1 left
		((pieces[getPos().row - 2][getPos().col - 1] == nullptr) || 
			(pieces[getPos().row - 2][getPos().col - 1]->getColor() != getColor())) && 
		(IsLegal({getPos().row - 2, getPos().col - 1}, pieces) == true) ) {
        vec.push_back(Pos{getPos().row - 2, getPos().col - 1});
	}

	if ((getPos().row - 1 >= 0) && (getPos().col - 2 >= 0) &&    //moving 1 up - 2 left
		((pieces[getPos().row - 1][getPos().col - 2] == nullptr) || 
			(pieces[getPos().row - 1][getPos().col - 2]->getColor() != getColor())) && 
		(IsLegal({getPos().row - 1, getPos().col - 2}, pieces) == true) ) {
        vec.push_back(Pos{getPos().row - 1, getPos().col - 2});
	}

	if ((getPos().row - 2 >= 0) && (getPos().col + 1 <= 7) &&    //moving 2 up - 1 right
		((pieces[getPos().row - 2][getPos().col + 1] == nullptr) || 
			(pieces[getPos().row - 2][getPos().col + 1]->getColor() != getColor())) && 
		(IsLegal({getPos().row - 2, getPos().col + 1}, pieces) == true) ) {
        vec.push_back({getPos().row - 2, getPos().col + 1});
	}

	if ((getPos().row - 1 >= 0) && (getPos().col + 2 <= 7) &&    //moving 1 up - 2 right
		((pieces[getPos().row - 1][getPos().col + 2] == nullptr) || 
			(pieces[getPos().row - 1][getPos().col + 2]->getColor() != getColor())) && 
		(IsLegal({getPos().row - 1, getPos().col + 2}, pieces) == true) ) {
        vec.push_back({getPos().row - 1, getPos().col + 2});
	}

	if ((getPos().row + 2 <= 7) && (getPos().col - 1 >= 0) &&    //moving 2 down - 1 left
		((pieces[getPos().row + 2][getPos().col - 1] == nullptr) || 
			(pieces[getPos().row + 2][getPos().col - 1]->getColor() != getColor())) && 
		(IsLegal({getPos().row + 2, getPos().col - 1}, pieces) == true) ) {
        vec.push_back({getPos().row + 2, getPos().col - 1});
	}

	if ((getPos().row + 1 <= 7) && (getPos().col - 2 >= 0) &&    //moving 1 down - 2 left
		((pieces[getPos().row + 1][getPos().col - 2] == nullptr) || 
			(pieces[getPos().row + 1][getPos().col - 2]->getColor() != getColor())) && 
		(IsLegal({getPos().row + 1, getPos().col - 2}, pieces) == true) ) {
        vec.push_back({getPos().row + 1, getPos().col - 2});
	}

	if ((getPos().row + 2 <= 7) && (getPos().col + 1 <= 7) &&    //moving 2 down - 1 right
		((pieces[getPos().row + 2][getPos().col + 1] == nullptr) || 
			(pieces[getPos().row + 2][getPos().col + 1]->getColor() != getColor())) && 
		(IsLegal({getPos().row + 2, getPos().col + 1}, pieces) == true) ) {
        vec.push_back({getPos().row + 2, getPos().col + 1});
	}

	if ((getPos().row + 1 <= 7) && (getPos().col + 2 <= 7) &&    //moving 1 down - 2 right
		((pieces[getPos().row + 1][getPos().col + 2] == nullptr) || 
			(pieces[getPos().row + 1][getPos().col + 2]->getColor() != getColor())) && 
		(IsLegal({getPos().row + 1, getPos().col + 2}, pieces) == true) ) {
        vec.push_back({getPos().row + 1, getPos().col + 2});
	}

	return vec;
}

Knight::Knight(Color c, Pos pos, bool hasMoved): Piece(c ,pos, hasMoved) {}

void Knight::print(std::ostream& out) const {
    if (getColor() == White) out << 'N';
    else out << 'n';
}

Knight::~Knight() {}

