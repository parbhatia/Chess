#ifndef BOARD_H
#define BOARD_H
#include "color.h"
#include "pos.h"
#include "move.h"
#include "textdisplay.h"

class Piece;

class Board {
	std::vector <Piece*> pieces; //current pieces on board
    std::vector <Move*> moves;
	TextDisplay* td;
	public:
	void insert (Pos pos, char letter);
	void remove (Pos pos);
	void updateTD(Pos oldpos, Pos newpos, char promo);
	std::vector<std::vector<Piece*>> getPieces();
    std::vector <Move*>* getMoves();
	Board();
	~Board();
    friend std::ostream &operator<<(std::ostream &os, const Board &b);
};
#endif
