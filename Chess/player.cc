#include "board.h"
#include "player.h"
#include "pos.h"
#include <vector>
using namespace std;

bool Player::LegalMoveExists() {
    for (auto &row:B->getPieces()) {
        for(auto &p: row){
            if (p != nullptr && p->getColor() == color) {//skipping empty cells and opponent pieces
            vector <Pos> possibleMoves = p->getPossibleMoves(B->getPieces());
                for (auto &m:possibleMoves) {/*legal move found if king is
                                              not attacked after the move*/
                    B->makeTheMove(p, B->getPieces()[m.row][m.col]);
                    if (!B->isAttacked(king->getPos())) {
                        B->undo();
                        return true;
                    }
                    B->undo();
                }
            }
        }
    }
    
//no legal move found at this point
return false;
}

void Player::setKing(King* k) {
    king = k;
}

King* Player::getKing() {
    return king;
}

Player::Player(Color color, Board* B, King* king):
color{color}, B{B}, king{king} {}
