#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "pos.h"
#include "color.h"

class Rook: public Piece {
public:
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	Rook(Color c, Pos pos, bool hasMoved = false);
};

#endif
