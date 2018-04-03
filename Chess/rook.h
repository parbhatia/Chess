#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "pos.h"
#include <vector>
#include "color.h"

class Rook: public Piece {
	bool IsLegal(Pos newPos, vector <vector<Piece*>> pieces) override;
	vector<Pos> getPossibleMoves(vector <vector<Piece*>> pieces) override;
	Rook(Color c, Pos pos, bool hasMoved);
};

#endif
