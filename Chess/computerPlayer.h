#include "player.h"

class ComputerPlayer: public Player {
	string lvl;
	public:
	void move(string oldPos, string newPos, char prm);
	//might not need ctor/dtor:
	ComputerPlayer();
	~ComputerPlayer();
};
