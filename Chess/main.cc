#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "pos.h"
#include "piece.h"
#include "player.h"
#include "humanPlayer.h"
//#include "computerPlayer.h"
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
using namespace std;

int main() {
    cout << "DEBUG: entered main" << endl;
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
        cout << "DEBUG: entered outer while loop" << endl;
        ///////// GAME SETUP: RESETS EVERY GAME /////////
        Board b;
        Player *wplayer = NULL;
        Player *bplayer = NULL;
        King *wking = new King(White,{-1,-1}); //WILL BE SMART PTR
        King *bking = new King(Black,{-1,-1}); //WILL BE SMART PTR
        bool game_finished = false;
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
                            //REDISPLAY BOARD
                            cout << b;
                        }
                    }
                    else if (letter == 'P' || letter == 'p') {
                        if (pos.row != 0 && pos.row != 7) { //checks if pawn is not in end rows
                            b.insert(pos,letter);
                            //REDISPLAY BOARD
                            cout << b;
                        }
                        else {
                            cout << "Invalid pawn placement." << endl;
                        }
                    }
                    else {
                        b.insert(pos,letter);
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
                    ///////////ADD
                    /*if (wplayer->isChecked() || bplayer->isChecked()) {
                        king_in_check = true;
                    }*/
                    //////////////
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
        }//end of setup
        if (cmd == "game") {
            cout << "DEBUG: entered game" << endl;
            //CREATE PLAYERS
            string wh;
            string bl;
            cin >> wh >> bl;
            //White player
            if (wh == "human") { wplayer = new HumanPlayer(White, &b, nullptr); }
            if (wh == "computer1") {};
            if (wh == "computer2") {};
            if (wh == "computer3") {};
            if (wh == "computer4") {};
            //Black player
            if (bl == "human") { bplayer = new HumanPlayer(Black, &b, nullptr); }
            if (bl == "computer1") {};
            if (bl == "computer2") {};
            if (bl == "computer3") {};
            if (bl == "computer4") {};
            cout << "DEBUG: players are: " << wh << " " << bl << endl;
            if (!already_setup) {
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
            while (game_finished == false) {
                cin >> cmd;
                cout << "DEBUG: entered inner game loop" << endl;
                if (cin.eof()) { //if player decides to end program mid game
                    cout << "Final Score:" << endl;
                    cout << "White: " << wpoints << endl;
                    cout << "Black: " << bpoints << endl;
                    return 0;
                }
                if (cmd == "resign") {
                    game_finished = true; //will break from game on next iteraiton
                    //update player points
                    if (turn == White) ++bpoints;
                    else ++wpoints;
                    break;
                }
                if (cmd == "move") {
                    cout << "DEBUG: entered move" << endl;
                    string s;
                    getline(cin,s);
                    char oldcol;
                    int oldrow;
                    char newcol;
                    int newrow;
                    char promotion = ' '; //need to assign promotion to ' '
                    stringstream ss(s);
                    ss >> oldcol >> oldrow >> newcol >> newrow >> promotion;
                    Pos old_pos = {8-oldrow, colmap.at(oldcol)};
                    Pos new_pos = {8-newrow, colmap.at(newcol)};
                    cout << "old pos is " << old_pos.row << old_pos.col << endl;
                    cout << "new pos is " << new_pos.row << new_pos.col << endl;
                    //find out who's turn it is
                    if (turn == White) {
                        try{
                            wplayer->move(old_pos, new_pos, promotion);
                            cout << "DEBUG: white move finished" << endl;
                        }
                        catch(invalid_move &o) {
                            cout << "Invalid move" << endl;
                            break;
                        }
                        catch(outofrange &o) {
                            cout << "Out of Range" << endl;
                            break;
                        }
                        catch(samepos &o) {
                            cout << "Same position" << endl;
                            break;
                        }
                        catch(emptycell &o) {
                            cout << "Empty cell" << endl;
                            break;
                        }
                        catch(notplayerpiece &o) {
                            cout << "Not Player Piece" << endl;
                            break;
                        }
                        catch(ownpiece &o) {
                            cout << "Own Piece" << endl;
                            break;
                        }
                        catch(illegalmove &o) {
                            cout << "Illegal Move" << endl;
                            break;
                        }
                        catch(tester &o) {
                            cout << "Test pickle rick" << endl;
                            break;
                        }
                    }
                    if (turn == Black) {
                        try{
                            bplayer->move(old_pos, new_pos, promotion);
                            cout << "DEBUG: black move finished" << endl;
                        }
                        catch(invalid_move &o) {
                            cout << "Invalid move" << endl;
                            break;
                        }
                        catch(outofrange &o) {
                            cout << "Out of Range" << endl;
                            break;
                        }
                        catch(samepos &o) {
                            cout << "Same position" << endl;
                            break;
                        }
                        catch(emptycell &o) {
                            cout << "Empty cell" << endl;
                            break;
                        }
                        catch(notplayerpiece &o) {
                            cout << "Not Player Piece" << endl;
                            break;
                        }
                        catch(ownpiece &o) {
                            cout << "Own Piece" << endl;
                            break;
                        }
                        catch(illegalmove &o) {
                            cout << "Illegal Move" << endl;
                            break;
                        }
                        catch(tester &o) {
                            cout << "Test pickle rick" << endl;
                            break;
                        }
                    }
                    
                    ///// REDISPLAY TEXTDISPLAY ////
                    cout<<b;
                    ///////// SWITCH TURNS /////////
                    if (turn == White) turn = Black;
                    if (turn == Black) turn = White;
                    ////////////////////////////////
                    
                }//end of move command
            }
            cout << "Please begin new game." << endl;
        }//end of game command
    }//end of one complete game, everything resets!
}

