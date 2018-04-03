#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "pos.h"
#include <vector>
#include "color.h"

class Bishop: public Piece {
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	Bishop(Color c, Pos Pos, bool hasMoved);
};

#endif
