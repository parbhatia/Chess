#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "piece.h"
#include "pos.h"
#include "color.h"

class Pawn: public Piece {
	bool enPassant;
	public:
	bool getPassant() override;
	void setPassant(bool val) override;
	bool IsLegal(Pos newPos, vector <vector<Piece*>> pieces) override;
	vector<Pos> getPossibleMoves(vector<vector<Piece*>> pieces) override;
	Pawn(Color c, Pos pos, bool hasMoved, bool enPassant);
};

#endif
