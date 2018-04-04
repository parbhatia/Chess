#ifndef CPLAYER_H
#define CPLAYER_H

#include "player.h"
#include <string>

class ComputerPlayer: public Player {
    std::string lvl;
	public:
    void move(const Pos, const Pos, const char prm) override;
    void moveLvl1();
    void moveLvl2();
    void moveLvl3();
    void moveLvl4();
	//might not need ctor/dtor:
	ComputerPlayer();
	~ComputerPlayer() override;
};
#endif
