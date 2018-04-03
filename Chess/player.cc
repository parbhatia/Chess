#include "board.h"
#include "player.h"
#include "pos.h"
bool Player::LegalMoveExists() {
	for (auto &p:B->getPieces()) {
		if (p != nullptr && p.getColor == color) {//skipping empty cells and opponent pieces
			vector <Pos> possibleMoves = p->getPossibleMoves();
			for (auto &m:possibleMoves) {/*legal move found if king is
							not attacked after the move*/
				makeTheMove(p, B->getPieces[m.row][m.col], B);
				if (!isAttacked(king, B->getPieces())) {
					B.undo();
					return true;
				}
					B.undo();
			}
		}
	}

//no legal move found at this point
return false;
}

void Player::setKing(King* k) {
	king = k;
}

void Player::getKing() {
	return king;
}

Player::Player(Color color, Board* B, King* king):
		color{color}, B{B}, king{king} {}