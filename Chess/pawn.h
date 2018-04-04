#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "pos.h"
#include "color.h"
#include <iostream>

class Pawn : public Piece {
	bool enPassant;
	public:
	bool isPawn() override;
	bool getPassant() override;
	void setPassant(bool val) override;
        bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
        std::vector<Pos> getPossibleMoves(std::vector<std::vector<Piece*>> pieces) override;
	Pawn(Color c, Pos pos, bool hasMoved = false, bool enPassant = false);
    void print(std::ostream& out) const override;
};

#endif
