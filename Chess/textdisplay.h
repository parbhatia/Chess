#ifndef TEXT_DISPLAY
#define TEXT_DISPLAY
#include <vector>
#include <string>
#include "pos.h"
class Piece;

class TextDisplay {
    std::vector<std::vector<char>> theDisplay;
	public:
	void insert (Pos pos, char letter);
	void remove (Pos pos);
	void move(Pos old_pos, Pos new_pos, char promo);
	TextDisplay();
	friend std::ostream &operator<<(std::ostream &os, const TextDisplay &td);
};



#endif
