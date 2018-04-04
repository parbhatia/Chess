#ifndef BOARD_H
#define BOARD_H
#include "color.h"
#include <vector>
#include "pos.h"
#include "move.h"
#include "piece.h"
#include <iostream>

class Board {
    std::vector<std::vector <Piece*>> pieces; //all pieces on board
    std::vector <Move*> moves;
    int count;
    public:
    std::vector <Move*> getMoves();
    void setCount(char c, int i=1);
    int getCount() const;
    void insert (Pos pos, char letter);
    void insert (Piece *p);
    void remove (Pos pos);
    void updateTD(Pos oldpos, Pos newpos, char promo);
    std::vector<std::vector<Piece*>> getPieces() const;
    bool outOfRange(const Pos p) const;
    bool isAttacked(Pos cellPos);
    void makeTheMove(Pos mPos, Pos tPos, char prm = 'Q');
    void undo();
    Board();
    ~Board();
    friend std::ostream &operator<<(std::ostream &os, const Board &b);
};
#endif
