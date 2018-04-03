#include "humanPlayer.h"
#include "pos.h"
#include <iostream>
using namespace std;

void HumanPlayer::move(Pos oldPos, Pos newPos, char prm){
	Piece* curPiece = B->getPieces()[oldPos.row][oldPos.col];
	Piece* target = B->getPieces()[newPos.row][newPos.col];//piece at newPos

	if (B->outOfRange(oldPos) || B->outOfRange(newPos)) { //out of the board
		cout << "INVALID" << endl;
	}
	else if (oldPos.col == newPos.col && oldPos.row == newPos.row) {//oldPos == newPos
		cout << "INVALID" << endl;
	}
	else if (curPiece == NULL) {//empty cell
		std::cout << "INVALID" << std::endl;
	}
	else if (curPiece->getColor() != color) { //not player's piece
        cout << "INVALID" << endl;
	}
	else if (target != NULL && target->getColor() == color) {//player capturing its own piece
        cout << "INVALID" << endl;
	}
	else {
		if(curPiece->IsLegal(newPos, B->getPieces())) {
			B->makeTheMove(curPiece, target, prm);
			if (B->isAttacked(king->getPos()) == true){
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
