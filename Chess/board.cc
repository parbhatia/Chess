#include "board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Piece;
class TextDisplay;
class XWindow;

class Board {
	vector<vector<Piece*>> pieces; //all pieces on board
	TextDisplay* td = NULL;
	public:
	void insert (Pos pos, char letter) {
        int r = pos.row;
        int c = pos.col;
        if (letter == 'R') { pieces[r][c] = new Rook(White,pos); }
        else if (letter == 'N') { pieces[r][c] = new Knight(White,pos); }
        else if (letter == 'B') { pieces[r][c] = new Bishop(White,pos); }
        else if (letter == 'Q') { pieces[r][c] = new Queen(White,pos); }
        else if (letter == 'K') { pieces[r][c] = new King(White,pos); }
        else if (letter == 'P') { pieces[r][c] = new Pawn(White,pos); }
        else if (letter == 'r') { pieces[r][c] = new Rook(Black,pos); }
        else if (letter == 'n') { pieces[r][c] = new Knight(Black,pos); }
        else if (letter == 'b') { pieces[r][c] = new Bishop(Black,pos); }
        else if (letter == 'q') { pieces[r][c] = new Queen(Black,pos); }
        else if (letter == 'k') { pieces[r][c] = new King(Black,pos); }
        else { pieces[r][c] = new Pawn(Black,pos); } //letter is 'p'
        //notify TextDisplay of insert
        td->insert(pos,letter);
    }
	void remove (Pos pos) {
        pieces[pos.row][pos.col] = NULL;
        //notify TextDisplay of remove
        td->remove(pos);
    }
    vector<vector<Piece*>> getPieces() { return pieces; }
	Board() { //sets up new 8x8 board
        td = new TextDisplay();
        for(int i=0; i<8; ++i) { 
            vector<*Pieces> P;
            for (int j=0; j<8; ++j) {
                P.emplace_back(NULL);
            }
            pieces.emplace_back(P);
        }
    }

    void notify(Pos pos char promo) {
        td->move(pos,promo);
    }

    bool ischeck(Pos kpos, Pos) {}

	~Board();
};

friend ostream &operator<<(ostream &os, const Board &b) {
    out<<(*td);
    return out;
}

void makeTheMove(Piece* moved, Piece* target){
	const Pos mPos = moved->getPos(); //moving from mPos
	const Pos tPos = target->getPos(); //moving to tPos
	bool RegularMove = true;

	//possible enPassant capture:
	if (((mPos.row == 3 && tPos.row == 2) || (mPos.row == 4 && tPos.row == 5)) &&
		(abs(mPos.col - tPos.col) == 1) && 
		(target == nullptr) &&
		(moved->getPassant() == true)) {
        //We do not need to check (pieces[mPos.row][tPos.col]->getPassant() == true))
        //since we already checked that in IsLegal
		RegularMove = false;
	    Move *m = new Move(mPos, tPos, pieces[mPos.row][tPos.col], "enPassantCapture");
	    moves->emplace_back(m);
   		target = moved; //capturing pawn moves to target
   		moved = nullptr; //old position of the capturing pawn
   		pieces[mPos.row][tPos.col] = nullptr; //position of the captured pawn

   	}

   	if ((moves.empty() == false) && (moves.back()->specialMove == "enPassantCapture")) {
		//Setting enPassant field of the pieces to false after enPassantCapture
		//We don't set enPassant field of captured piece to false
   		pieces[moves.back()->newPos.row][moves.back()->newPos.col]->setPassant(false);
   		if ((moves.back()->newPos.col + 1 == moves.back()->oldPos.col) &&
   			(moves.back()->oldPos.col - 2 >= 0)) {
   			pieces[moves.back()->oldPos.row][moves.back()->oldPos.col - 2]->setPassant(false);
   	}
   	if ((moves.back()->newPos.col - 1 == moves.back()->oldPos.col) &&
   		(moves.back()->oldPos.col + 2 <= 7)) {
   		pieces[moves.back()->oldPos.row][moves.back()->oldPos.col + 2]->setPassant(false);
   }
}

if ((moves.empty() == false) && (moves.back()->specialMove == "enPassantSetup")) {
    	//if the next move is not enPassant we set all enPassant fields to false before
    	//the other conditions
	pieces[moves.back()->newPos.row][moves.back()->newPos.col]->setPassant(false);
	pieces[moves.back()->newPos.row][moves.back()->newPos.col + 1]->setPassant(false);
	pieces[moves.back()->newPos.row][moves.back()->newPos.col - 1]->setPassant(false);
}


	if ((moved->getMoved() == false) && //possible enPassant setup (2 forward move)
		((mPos.row == 1 && tPos.row == 3) || (mPos.row == 6 && tPos.row == 4))) {
		RegularMove = false;
	    Move *m = new Move(mPos, tPos, nullptr, "enPassantSetup");
	    moves->emplace_back(m);
	    moved->setPassant(true);
			target = moved; //2 forward move
			moved = nullptr; 
			pieces[tPos.row][tPos.col - 1]->setPassant(true);
			pieces[tPos.row][tPos.col + 1]->setPassant(true);
		}


	if ((moved->getMoved() == false) &&   //short-castling condition for both colors
		((mPos.row == 0) || (mPos.row == 7)) && (mPos.col = 4) &&
		(tPos.row == 6)) {
		RegularMove = false;
	Move *m = new Move(mPos, tPos, nullptr, "Castling");
	moves->emplace_back(m);
	target = moved;
	moved = nullptr;
	    pieces[mPos.row][5] = pieces[mPos.row][7]; //moves the castle to the new loc
	    pieces[mPos.row][7] = nullptr; //
	}

	if ((moved->getMoved() == false) &&   //long-castling condition for both colors
		((mPos.row == 0) || (mPos.row == 7)) && (mPos.col = 4) &&
		(tPos.row == 2)) {
		RegularMove = false;
	Move *m = new Move(mPos, tPos, nullptr, "Castling");
	moves->emplace_back(m);
	target = moved;
	moved = nullptr;
	    pieces[mPos.row][5] = pieces[mPos.row][0]; //moves the castle to the new loc
	    pieces[mPos.row][0] = nullptr; //
	}

	if(RegularMove == true) {
		Move* m = new Move(mPos, tPos, target, "Regular");
		moves.emplace_back(m); //info about move is pushed to moved vec in board
		target = moved; //target cell points to moved piece
		moved = nullptr; //freeing old cell
	}
	
}

bool outOfRange(const Pos p) {
	if (p.row > 7 || p.col > 7) return true;
	else if (p.row < 0 || p.col < 0) return true;

return false;
}

bool isAttacked(Pos cellPos, vector< vector<Piece*> > pieces) {
	for(auto &p:pieces) {
		//skipping owned pieces and empty cells:
		if(p == nullptr) continue;
		if(color == p->getColor()) continue;
		//checking if p can move to curPos
		if (p->IsLegal(curPos, p)){
			return true;
		}
	}

return false; //has checked all enemy pieces and none of them attacks player's king
}


