#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "pos.h"
#include "color.h"


class Queen: public Piece {
	bool IsLegal(Pos newPos, vector <vector<Piece*>> pieces) override;
	vector<Pos> getPossibleMoves(vector<vector<Piece*>> pieces) override;
	Queen(Color c, Pos pos, bool hasMoved = false);
};

#endif
