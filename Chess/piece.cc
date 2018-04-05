#include "piece.h"
#include <iostream>
using namespace std;

int Piece::getPriority() {
	return priority;
}
	
void Piece::setMoved(bool val) {
    if (val == true) hasMoved = true;
    else hasMoved = false;
}

bool Piece::getMoved() {
	return hasMoved;
}

Color Piece::getColor() const{
	return color;
}

void Piece::updatePos(Pos newPos) {
	pos.row = newPos.row;
	pos.col = newPos.col;
}

Pos Piece::getPos() {
	return pos;
}

std::ostream& operator<<(std::ostream& out, const Piece &p) {
    p.print(out);
    return out;
}

bool Piece::isPawn() {
	return false;
}

bool Piece::getPassant() {
	return false;
}

void Piece::setPassant(bool val) {}

Piece::Piece(Color c, Pos pos, int priority, bool hasMoved): color{c}, pos{pos}, priority{priority}, hasMoved{hasMoved} {}

Piece::~Piece() {}
