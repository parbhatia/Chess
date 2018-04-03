#include "player.h"

class ComputerPlayer: public Player {
	string lvl;
	public:
	void move(string oldPos, string newPos, string Permission);
	//might not need ctor/dtor:
	ComputerPlayer();
	~ComputerPlayer();
};
