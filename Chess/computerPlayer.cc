#include "computerPlayer.h"
#include "pos.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "player.h"
#include "errors.h"
#include <cmath>
using namespace std;

class Piece;

vector<vector<Pos>> ComputerPlayer::getLegalMoves() {/* returns vector that holds the list of legal move positions of a
										 piece(if there is any) and the piece position at the end */
	vector <vector<Pos>> legalMoves;

    for (auto &row:B->getPieces()) { //iterating through rows in board
        for(auto &p:row){ //iterating through pieces in every row

            if (p != nullptr && p->getColor() == color) {//skipping empty cells and opponent pieces

	            vector <Pos> possibleMoves = p->getPossibleMoves(B->getPieces()); //getting possible moves
	            vector <Pos> legalMovesOfPiece;
	            int curPos = 0;
                
                while(curPos < possibleMoves.size()) {
                    B->makeTheMove(p->getPos(), possibleMoves[curPos]);
                    if (!B->isAttacked(king->getPos())) { /* target pos added to legalMoves if it's legal */
                        legalMovesOfPiece.push_back(possibleMoves[curPos]);
                    }
                    B->undo(); //undoing move after checking if it is legal
                    ++curPos;
                }

                if (legalMovesOfPiece.size() > 0) {
                	legalMovesOfPiece.push_back(p->getPos());
                	legalMoves.push_back(legalMovesOfPiece);
                    //cout << legalMovesOfPiece.size() << endl;
                }
            }
        }
    }

return legalMoves;
}

void ComputerPlayer::move(Pos curPos, Pos newPos, char prm){ //assumes lvl is valid (i.e 1-4)
	if(lvl == "1"){
		moveLvl1();
	}
	else if (lvl == "2"){
		moveLvl2();
	}
	else if (lvl == "3"){
		moveLvl3();
	}
	else moveLvl4();
}

void ComputerPlayer::moveLvl1(){
    srand((unsigned) time(NULL));
	vector<vector<Pos>> legalMoves = getLegalMoves(); //getting every legal move of the player
    int PiecePosIndex;
    if (legalMoves.size() == 1){//only 1 piece has any legal move
        PiecePosIndex = 0;
    }
    else {// more than 1 piece has a legal move
        PiecePosIndex = rand() % (legalMoves.size() - 1);
    } //good
    //cout << "size is" << legalMoves.size() << endl; //good
    //cout << "pos index is" << PiecePosIndex << endl; //good
	//choosing a random target pos for the Piece stored in PiecePosIndex
	//since piece is stored at the end, we select random index from the range [0, size-2]
    //cout << "legalmoves size " << legalMoves[PiecePosIndex].size() << endl;
    int TargetPosIndex;
    
    if (legalMoves[PiecePosIndex].size() == 2){//only 1 legal move for the piece
        TargetPosIndex = 0;
    }
    else {// more than 1 legal moves
        TargetPosIndex = rand() % (legalMoves[PiecePosIndex].size() - 1);
    }
    
    
    //cout << "targetposindex is: " << TargetPosIndex << endl;
	Pos PiecePos = legalMoves[PiecePosIndex].back();
	Pos TargetPos = legalMoves[PiecePosIndex][TargetPosIndex];
	//getLegalMoves() function returns only legal moves, so we're safe:
	B->makeTheMove(PiecePos, TargetPos);
}

void ComputerPlayer::moveLvl2(){
	//int priority = 0;
	//vector <vector<Pos>*> legalMoves = getLegalMoves();
	//vector <vector<Pos>> preferredMovePos(2);

}

void ComputerPlayer::moveLvl3(){}

void ComputerPlayer::moveLvl4(){}

ComputerPlayer::ComputerPlayer(Color color, Board* B, King* king, string lvl): Player(color, B, king), lvl{lvl} {}

ComputerPlayer::~ComputerPlayer() {}

