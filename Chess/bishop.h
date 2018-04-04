#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "pos.h"
#include <vector>
#include "color.h"
#include <iostream>

class Bishop: public Piece {
public:
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	Bishop(Color c, Pos Pos, bool hasMoved = false);
    void print(std::ostream& out) const override;
};
#endif
