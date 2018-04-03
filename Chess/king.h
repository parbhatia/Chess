#ifndef KING_H
#define KING_H
#include "piece.h"
#include "pos.h"
#include "color.h"

class King: public Piece {
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	King(Color c, Pos pos, bool hasMoved = false);
};

#endif
