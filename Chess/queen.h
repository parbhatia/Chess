#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "pos.h"
#include "color.h"

class Queen: public Piece {
public:
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector<std::vector<Piece*>> pieces) override;
	Queen(Color c, Pos pos, bool hasMoved = false);
};

#endif
