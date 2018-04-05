#ifndef CPLAYER_H
#define CPLAYER_H
#include "player.h"
#include "color.h"
#include "king.h"

class ComputerPlayer: public Player {
    std::string lvl;
	public:
    std::vector<std::vector<Pos>> getLegalMoves();
    void move(Pos curPos = {0,0}, Pos newPos = {0,0}, char prm = 'Q') override;
    void moveLvl1();
    void moveLvl2();
    void moveLvl3();
    void moveLvl4();
	//might not need ctor/dtor:
    ComputerPlayer(Color color, Board* B, King* king, std::string lvl);
	~ComputerPlayer() override;
};
#endif
