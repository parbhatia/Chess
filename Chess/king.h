#ifndef KING_H
#define KING_H

#include <vector>
#include "piece.h"
#include "pos.h"
#include "color.h"

class King: public Piece {
	bool IsLegal(Pos newPos, vector <vector<Piece*>> pieces) override;
	vector<Pos> getPossibleMoves(vector <vector<Piece*>> pieces) override;
	King(Color c, Pos pos, bool hasMoved = false);
};

#endif
