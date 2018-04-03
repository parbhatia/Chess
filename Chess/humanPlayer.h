#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "king.h"

class HumanPlayer: public Player {
	public:
	void move(Pos oldPos, Pos newPos, char prm) override;
	HumanPlayer(Color color, Board* B, King* king = NULL);
	~HumanPlayer();
};
#endif
