#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "pos.h"
#include "color.h"
#include <iostream>

class Piece {
	const Color color;
	Pos pos;
	bool hasMoved;
    virtual void print(std::ostream& out) const = 0;
	public:
	void setMoved(bool val);
	bool getMoved();
	Color getColor() const;
	void updatePos(Pos newPos);
	Pos getPos();
	virtual bool isPawn();
	virtual bool getPassant();
	virtual void setPassant(bool val);
        virtual bool IsLegal(Pos newPos, std::vector <std::vector<Piece*>> pieces) = 0;
        virtual std::vector<Pos> getPossibleMoves(std::vector<std::vector<Piece*>> pieces) = 0;
	Piece(Color c, Pos pos, bool hasMoved = false);
	//No need a destructor since there is no heap allocated field and default dest is enough
    friend std::ostream& operator<<(std::ostream& out, const Piece &p);
};


#endif
