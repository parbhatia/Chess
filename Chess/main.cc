#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "pos.h"
#include "piece.h"
#include "player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "board.h"
#include "piecepositions.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "color.h"
#include "move.h"
#include "errors.h"
#include "window.h"
using namespace std;

int main() {
    string cmd;
    
    // SCOREBOARD //
    int wpoints = 0;
    int bpoints = 0;
    ////////////////
    
    //creating map of column commands to make parsing column positions easier
    map<char, Col> colmap;
    colmap['a'] = Col::a;
    colmap['b'] = Col::b;
    colmap['c'] = Col::c;
    colmap['d'] = Col::d;
    colmap['e'] = Col::e;
    colmap['f'] = Col::f;
    colmap['g'] = Col::g;
    colmap['h'] = Col::h;
    
    while (true) {
        ///////// GAME SETUP: RESETS EVERY GAME /////////
        Board b;
        Xwindow *x = new Xwindow(8,8);
        Player *wplayer = NULL;
        Player *bplayer = NULL;
        King *wking = new King(White,{-1,-1});
        King *bking = new King(Black,{-1,-1});
        bool already_setup = false;
        bool setup_conditions_met = false;
        Color turn = White; // white goes first by default
        /////////////////////////////////////////////////
        cin >> cmd;
        if (cin.eof()) { //end program command
            cout << "Final Score:" << endl;
            cout << "White: " << wpoints << endl;
            cout << "Black: " << bpoints << endl;
            return 0;
        }
        if (cmd == "setup") {
            cout << b;
            already_setup = true;
            bool w_kingset = false;
            bool b_kingset = false;
            bool king_in_check = false;
            while(true) {
                cin >> cmd;
                if (cmd == "+") {
                    char letter; // holds letter
                    char col; //col pos
                    int row; //row pos
                    cin >> letter >> col >> row;
                    Pos pos = {8-row,colmap.at(col)};
                    if (letter == 'K') {
                        if (w_kingset) {
                            cout << "Black king already assigned." << endl;
                        }
                        else {
                            wking->updatePos(pos);
                            b.insert(wking);
                            w_kingset = true;
                            b.setCount('+',1);
                            //REDISPLAY BOARD
                            cout << b;
                        }
                    }
                    else if (letter == 'k') {
                        if (b_kingset) {
                            cout << "White king already assigned." << endl;
                        }
                        else {
                            bking->updatePos(pos);
                            b.insert(bking);
                            b_kingset = true;
                            b.setCount('+',1);
                            //REDISPLAY BOARD
                            cout << b;
                        }
                    }
                    else if (letter == 'P' || letter == 'p') {
                        if (pos.row != 0 && pos.row != 7) { //checks if pawn is not in end rows
                            b.insert(pos,letter);
                            b.setCount('+',1);
                            //REDISPLAY BOARD
                            cout << b;
                        }
                        else {
                            cout << "Invalid pawn placement." << endl;
                        }
                    }
                    else {
                        b.insert(pos,letter);
                        b.setCount('+',1);
                        //REDISPLAY BOARD
                        cout << b;
                    }
                }
                if (cmd == "=") {
                    string c; //stores color
                    cin >> c;
                    if (c == "black") turn = Black;
                }
                if (cmd == "-") {
                    char col;
                    int row;
                    cin >> col >> row;
                    Pos pos = {8-row,colmap.at(col)};
                    if (b.getPieces()[pos.row][pos.col] != nullptr) { //take action only if there is a piece at pos
                        if (wking->getPos().row == pos.row && wking->getPos().col == pos.col) {
                            wking->updatePos({-1,-1});
                            w_kingset = false;
                        }
                        if (bking->getPos().row == pos.row && bking->getPos().col == pos.col) {
                            bking->updatePos({-1,-1});
                            b_kingset = false;
                        }
                        b.remove(pos);
                        b.setCount('-',1);
                        //REDISPLAY BOARD
                        cout << b;
                    }
                }
                if (cmd == "done") {
                    //Check setup conditions
                    if (w_kingset == false){
                        cout << "White king not set." << endl;
                    }
                    if (b_kingset == false) {
                        cout << "Black king not set." << endl;
                    }
                    //check if kings are check
                    if (b.isAttacked(wking->getPos()) || b.isAttacked(bking->getPos())) {
                        king_in_check = true;
                    } else {
                        king_in_check = false;
                    }
                    if (!king_in_check && w_kingset && b_kingset) setup_conditions_met = true;
                    if (setup_conditions_met) {
                        break;
                    }
                    else {
                        cout << "Setup conditions not met." << endl;
                    }
                }
            }
            cout << "Setup complete." << endl;
            cout << "Please begin new game." << endl;
            cin >> cmd;
        }//end of setup
        if (cmd == "game") {
            //CREATE PLAYERS
            string wh;
            string bl;
            cin >> wh >> bl;
            //White player
            if (wh == "human") { wplayer = new HumanPlayer(White, &b, nullptr); }
            if (wh == "computer1") { wplayer = new ComputerPlayer(White, &b, nullptr, "1"); };
            if (wh == "computer2") {};
            if (wh == "computer3") {};
            if (wh == "computer4") {};
            //Black player
            if (bl == "human") { bplayer = new HumanPlayer(Black, &b, nullptr); }
            if (bl == "computer1") { bplayer = new ComputerPlayer(Black, &b, nullptr, "1"); };
            if (bl == "computer2") {};
            if (bl == "computer3") {};
            if (bl == "computer4") {};
            if (!already_setup) {
                b.setCount('+',32);
                //inserting white player pieces
                b.insert(R1,'R');
                b.insert(N1,'N');
                b.insert(B1,'B');
                b.insert(Q,'Q');
                b.insert(K,'K');
                b.insert(B2,'B');
                b.insert(N2,'N');
                b.insert(R2,'R');
                b.insert(P1,'P');
                b.insert(P2,'P');
                b.insert(P3,'P');
                b.insert(P4,'P');
                b.insert(P5,'P');
                b.insert(P6,'P');
                b.insert(P7,'P');
                b.insert(P8,'P');
                //inserting black player pieces
                b.insert(r1,'r');
                b.insert(n1,'n');
                b.insert(b1,'b');
                b.insert(q,'q');
                b.insert(k,'k');
                b.insert(b2,'b');
                b.insert(n2,'n');
                b.insert(r2,'r');
                b.insert(p1,'p');
                b.insert(p2,'p');
                b.insert(p3,'p');
                b.insert(p4,'p');
                b.insert(p5,'p');
                b.insert(p6,'p');
                b.insert(p7,'p');
                b.insert(p8,'p');
                //Players set their king pointers
                wplayer->setKing(b.getPieces()[7][4]);
                bplayer->setKing(b.getPieces()[0][4]);
            }
            else { //already setup is true
                //Players set their kings
                wplayer->setKing(wking);
                bplayer->setKing(bking);
            }
            cout << b;
            while (1) {
                cin >> cmd;
                if (cin.eof()) { //if player decides to end program mid game
                    cout << "Final Score:" << endl;
                    cout << "White: " << wpoints << endl;
                    cout << "Black: " << bpoints << endl;
                    delete wking;
                    delete bking;
                    return 0;
                }
                if (cmd == "resign") {
                    //update player points
                    if (turn == White) ++bpoints;
                    else ++wpoints;
                    break;
                }
                if (cmd == "move") {
                    string s;
                    getline(cin,s);
                    char oldcol;
                    int oldrow;
                    char newcol;
                    int newrow;
                    char promotion = ' '; //need to assign promotion to ' '
                    stringstream ss(s);
                    ss >> oldcol >> oldrow >> newcol >> newrow >> promotion;
                    if (s == "") { // computer move
                        if (turn == Black) {
                            try {
                                bplayer->move();
                            }
                            catch(king_attacked &o) {
                                cout << "King in check. Try again." << endl;
                                continue;
                            }
                            catch(invalid_move &o) {
                                cout << "Invalid move. Try Again." << endl;
                                continue;
                            }
                            catch(outofrange &o) {
                                cout << "Out of Range. Try Again." << endl;
                                continue;
                            }
                            catch(samepos &o) {
                                cout << "Same position. Try Again." << endl;
                                continue;
                            }
                            catch(emptycell &o) {
                                cout << "Empty cell. Try Again." << endl;
                                continue;
                            }
                            catch(notplayerpiece &o) {
                                cout << "Not Player Piece. Try Again." << endl;
                                continue;
                            }
                            catch(ownpiece &o) {
                                cout << "Own Piece. Try Again." << endl;
                                continue;
                            }
                            catch(illegalmove &o) {
                                cout << "Illegal Move. Try Again." << endl;
                                continue;
                            }
                            catch(castling_fail &o) {
                                cout << "Castling invalid. Try Again." << endl;
                                continue;
                            }
                            catch(tester &o) {
                                cout << "Test pickle rick. Try Again." << endl;
                                continue;
                            }
                        } else { // turn is White
                            try {
                                wplayer->move();
                            }
                            catch(king_attacked &o) {
                                cout << "King in check. Try again." << endl;
                                continue;
                            }
                            catch(invalid_move &o) {
                                cout << "Invalid move. Try Again." << endl;
                                continue;
                            }
                            catch(outofrange &o) {
                                cout << "Out of Range. Try Again." << endl;
                                continue;
                            }
                            catch(samepos &o) {
                                cout << "Same position. Try Again." << endl;
                                continue;
                            }
                            catch(emptycell &o) {
                                cout << "Empty cell. Try Again." << endl;
                                continue;
                            }
                            catch(notplayerpiece &o) {
                                cout << "Not Player Piece. Try Again." << endl;
                                continue;
                            }
                            catch(ownpiece &o) {
                                cout << "Own Piece. Try Again." << endl;
                                continue;
                            }
                            catch(illegalmove &o) {
                                cout << "Illegal Move. Try Again." << endl;
                                continue;
                            }
                            catch(castling_fail &o) {
                                cout << "Castling invalid. Try Again." << endl;
                                continue;
                            }
                            catch(tester &o) {
                                cout << "Test pickle rick. Try Again." << endl;
                                continue;
                            }
                        }
                    }
                    else { // human move
                        Pos old_pos = {8-oldrow, colmap.at(oldcol)};
                        Pos new_pos = {8-newrow, colmap.at(newcol)};
                        //find out who's turn it is
                        if (turn == Black) {
                            try {
                                bplayer->move(old_pos, new_pos, promotion);
                            }
                            catch(king_attacked &o) {
                                cout << "King in check. Try again." << endl;
                                continue;
                            }
                            catch(invalid_move &o) {
                                cout << "Invalid move. Try Again." << endl;
                                continue;
                            }
                            catch(outofrange &o) {
                                cout << "Out of Range. Try Again." << endl;
                                continue;
                            }
                            catch(samepos &o) {
                                cout << "Same position. Try Again." << endl;
                                continue;
                            }
                            catch(emptycell &o) {
                                cout << "Empty cell. Try Again." << endl;
                                continue;
                            }
                            catch(notplayerpiece &o) {
                                cout << "Not Player Piece. Try Again." << endl;
                                continue;
                            }
                            catch(ownpiece &o) {
                                cout << "Own Piece. Try Again." << endl;
                                continue;
                            }
                            catch(illegalmove &o) {
                                cout << "Illegal Move. Try Again." << endl;
                                continue;
                            }
                            catch(castling_fail &o) {
                                cout << "Castling invalid. Try Again." << endl;
                                continue;
                            }
                            catch(tester &o) {
                                cout << "Test pickle rick. Try Again." << endl;
                                continue;
                            }
                        } else { //turn is White
                            try {
                                wplayer->move(old_pos, new_pos, promotion);
                            }
                            catch(king_attacked &o) {
                                cout << "King in check. Try again." << endl;
                                continue;
                            }
                            catch(invalid_move &o) {
                                cout << "Invalid move. Try Again." << endl;
                                continue;
                            }
                            catch(outofrange &o) {
                                cout << "Out of Range. Try Again." << endl;
                                continue;
                            }
                            catch(samepos &o) {
                                cout << "Same position. Try Again." << endl;
                                continue;
                            }
                            catch(emptycell &o) {
                                cout << "Empty cell. Try Again." << endl;
                                continue;
                            }
                            catch(notplayerpiece &o) {
                                cout << "Not Player Piece. Try Again." << endl;
                                continue;
                            }
                            catch(ownpiece &o) {
                                cout << "Own Piece. Try Again." << endl;
                                continue;
                            }
                            catch(illegalmove &o) {
                                cout << "Illegal Move. Try Again." << endl;
                                continue;
                            }
                            catch(castling_fail &o) {
                                cout << "Castling invalid. Try Again." << endl;
                                continue;
                            }
                            catch(tester &o) {
                                cout << "Test pickle rick. Try Again." << endl;
                                continue;
                            }
                        }
                    }
                    
                    //check stalemate for only 2 kings in board
                    if (b.getCount() == 2) {
                        cout << "Stalemate!" << endl;
                        break;
                    }
                    if (turn == White) {
                        bool legalexists = bplayer->LegalMoveExists();
                        if (b.isAttacked(bplayer->getKing()->getPos())) {
                            if (legalexists) {
                                cout << "Black is in check." << endl;
                            } else {
                                cout << "Checkmate! White wins!" << endl;
                                ++wpoints;
                                break;
                            }
                        } else {
                            if (legalexists == false) {
                                cout << "Stalemate!" << endl;
                                break;
                            }
                        }
                    }
                    if (turn == Black) {
                        bool legalexists = wplayer->LegalMoveExists();
                        if (b.isAttacked(wplayer->getKing()->getPos())) {
                            if (legalexists) {
                                cout << "White is in check." << endl;
                            } else {
                                cout << "Checkmate! Black wins!" << endl;
                                ++bpoints;
                                break;
                            }
                        } else {
                            if (legalexists == false) {
                                cout << "Stalemate!" << endl;
                                break;
                            }
                        }
                    }
                    
                    if (b.getMoves().back()->specialMove == "enPassantSetup") {
                        b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col]->setPassant(true);
                        if (!(b.outOfRange({b.getMoves().back()->newPos.row, b.getMoves().back()->newPos.col - 1})) &&
                            (b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col - 1] != nullptr) &&
                            (b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col - 1]->getColor() != turn)) {
                            b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col - 1]->setPassant(true);
                        }
                        if (!(b.outOfRange({b.getMoves().back()->newPos.row, b.getMoves().back()->newPos.col + 1})) &&
                            (b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col + 1] != nullptr) &&
                            (b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col + 1]->getColor() != turn)) {
                            b.getPieces()[b.getMoves().back()->newPos.row][b.getMoves().back()->newPos.col + 1]->setPassant(true);
                        }
                    }
                }
                else { //command unrecognized
                    cout << "Command unreognized. Try again." << endl;
                }
                ///// REDISPLAY TEXTDISPLAY ////
                cout<<b;
                ///////// SWITCH TURNS /////////
                if (turn == White) turn = Black;
                else turn = White;
                ////////////////////////////////
                
            }//end of game_finished
        }
        cout << "Begin new game." << endl;
    }//end of game command
}//end of one complete game, everything resets!

