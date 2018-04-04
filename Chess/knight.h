#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include "pos.h"
#include "color.h"
#include <iostream>

class Knight: public Piece {
public:
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	Knight(Color c, Pos pos, bool hasMoved = false);
    void print(std::ostream& out) const override;
};

#endif
