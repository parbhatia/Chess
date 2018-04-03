#include "player.h"
#include <iostream>

class ComputerPlayer: public Player {
    std::string lvl;
	public:
    void move(std::string oldPos, std::string newPos, char prm);
	//might not need ctor/dtor:
	ComputerPlayer();
	~ComputerPlayer() override;
};
