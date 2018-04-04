#include "humanPlayer.h"
#include "pos.h"
#include <iostream>
#include "player.h"
#include "errors.h"
using namespace std;

void HumanPlayer::move(Pos oldPos, Pos newPos, char prm){
	Piece* curPiece = B->getPieces()[oldPos.row][oldPos.col];
	Piece* target = B->getPieces()[newPos.row][newPos.col];//piece at newPos

	if (B->outOfRange(oldPos) || B->outOfRange(newPos)) { //out of the board
		throw(outofrange());
	}
	else if (oldPos.col == newPos.col && oldPos.row == newPos.row) {//oldPos == newPos
		throw(samepos());
	}
	else if (curPiece == NULL) {//empty cell
		throw(emptycell());
	}
	else if (curPiece->getColor() != color) { //not player's piece
        throw(notplayerpiece());
	}
	else if (target != NULL && target->getColor() == color) {//player capturing its own piece
        throw(ownpiece());
	}
	else {
		if(curPiece->IsLegal(newPos, B->getPieces())) {
			if(prm == ' ') {
				B->makeTheMove(oldPos, newPos);
			} else {
				B->makeTheMove(oldPos, newPos, prm);
			}
			if (B->isAttacked(king->getPos()) == true){
				B->undo();
                //not this error
				throw(invalid_move());
			}
			else {
				curPiece->setMoved(true);
			}
		}
		else { //last move attempt was illegal
			throw(illegalmove());
		}
	}
}

HumanPlayer::HumanPlayer(Color color, Board* B, King* king): Player(color, B, king) {}

HumanPlayer::~HumanPlayer() {}
