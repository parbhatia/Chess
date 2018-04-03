#ifndef MOVE_H
#define MOVE_H
#include "piece.h"
#include "pos.h"
#include <string>
struct Move{
    Pos oldPos, newPos;
    Piece *captured;
    std::string specialMove;
};

#endif
