#ifndef PLAYER_H
#define PLAYER_H
#include "piece.h"
#include "king.h"

class Board;

class Player {
	protected:
    Board* B;
    const Color color;
	King* king;
	public:
	//checks if player has any legal moves:
	bool LegalMoveExists();
	void setKing(King* K);
	King* getKing();
    virtual void move(const Pos curPos, const Pos newPos, char prm) = 0;
	Player(Color color, Board* B, King* king = NULL);
	~Player();
};

//should we make these Board methods?
void makeTheMove(Piece* moved, Piece* target, Board* b);
bool outOfRange(const Pos p);
bool isAttacked(Piece* p, std::vector<Piece*> pieces);

#endif
