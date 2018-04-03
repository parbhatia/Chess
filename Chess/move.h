#ifndef MOVE_H
#define MOVE_H

struct move{
    Pos oldPos, newPos;
    Piece *captured;
    string specialMove;
};

#endif
