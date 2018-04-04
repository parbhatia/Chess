#ifndef PLAYER_H
#define PLAYER_H
#include "piece.h"
#include "king.h"
#include "board.h"
#include <iostream>

class Player {
	protected:
    const Color color;
    Board* B;
	King* king;
	public:
	//checks if player has any legal moves:
	bool LegalMoveExists();
	void setKing(Piece* K);
	King* getKing();
    virtual void move(Pos curPos = {0,0}, Pos newPos = {0,0}, char prm = 'Q') = 0;
	Player(Color color, Board* B, King* king = NULL);
	virtual ~Player();
};

#endif
