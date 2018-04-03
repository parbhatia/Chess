#include "humanPlayer.h"
#include "pos.h"

HumanPlayer::void move(Pos oldPos, newPos, char prm){
	Piece* curPiece = B.getPieces[oldPos.row][oldPos.col];
	Piece* target = B.getPieces[newPos.row][newPos.col];//piece at newPos

	if (B->outOfRange(oldPos) || B->outOfRange(newPos)) { //out of the board
		std::cout << "INVALID" << std::endl;
	}
	else if (oldPos.col == newPos.col && oldPos.row == newPos.row) {//oldPos == newPos
		std::cout << "INVALID" << std::endl;
	}
	else if (curPiece == NULL) {//empty cell
		std::cout << "INVALID" << std::endl;
	}
	else if (curPiece->getColor() != color) { //not player's piece
	std::cout << "INVALID" << std::endl;
	}
	else if (target != NULL && target->color == color) {//player capturing its own piece
	std::cout << "INVALID" << std::endl;
	}
	else {
		if(IsLegal(newPos, B->getPieces())) {
			B->makeTheMove(curPiece, target);
			if (B->isAttacked(king->getPos(), B->getPieces()) == true){
				B->undo();
				std::cout << "INVALID" << std::endl;
			}
			else {
				curPiece->setMoved(true);
			}
		}
		else { //last move attempt was illegal
			std::cout << "INVALID" << std::endl;
		}
	}
}

HumanPlayer::HumanPlayer(Color color, Board* B, King* king): Player(color, B, king) {}

HumanPlayer::~HumanPlayer(){};
