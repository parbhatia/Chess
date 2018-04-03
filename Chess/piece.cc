#include "piece.h"
using namespace std;

void Piece::setMoved(bool val) {
	hasMoved = val;
}

bool Piece::getMoved() {
	return hasMoved;
}

Color Piece::getColor(){
	return color;
}

void Piece::updatePos(Pos newPos) {
	pos.row = newPos.row;
	pos.col = newPos.col;
}

Pos Piece::getPos() {
	return pos;
}

bool Piece::getPassant() {
	return false;
}

void Piece::setPassant(bool val) {}

Piece::Piece(Color c, Pos pos, bool hasMoved): color{c}, pos{pos}, hasMoved{hasMoved} {}
