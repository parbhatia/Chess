#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "pos.h"
#include "color.h"

class Piece {
	const Color color;
	Pos pos;
	bool hasMoved;
	public:
	void setMoved(bool val);
	bool getMoved();
	Color getColor();
	void updatePos(Pos newPos);
	Pos getPos();
	virtual bool getPassant();
	virtual void setPassant(bool val);
	virtual bool IsLegal(Pos newPos, vector <vector<Piece*>> pieces) = 0;
	virtual vector<Pos> getPossibleMoves(vector<vector<Piece*>> pieces) = 0;
	Piece(Color c, Pos pos, bool hasMoved = false);
	friend ostream& operator<<(ostream& out, const Piece& p);
	//No need a destructor since there is no heap allocated field and default dest is enough
};

#endif
