#ifndef KING_H
#define KING_H
#include "piece.h"
#include "pos.h"
#include "color.h"
#include <iostream>

class King: public Piece {
public:
    bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) override;
    std::vector<Pos> getPossibleMoves(std::vector <std::vector<Piece*>> pieces) override;
	King(Color c, Pos pos, int priority = 50, bool hasMoved = false);
    void print(std::ostream& out) const override;
    ~King() override;
};

#endif
