#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
#include <stdlib.h> 

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board *b = NULL;
    Side s;
    
    Move *doMove(Move *opponentsMove, int msLeft);
    int simpleScore(Side mover, Board *cop, Move* move);
    int miniMaxScore(Move *yourMove, Side mover);
    int miniMaxScore2(Move *yourMove, Side mover);
    int alphaBetaPruning(int depth, Board* node, int alpha, int beta, Side side, Move* move);
    vector<Move*> getPossibleMoves(Board* node, Side side);
    Side getOppositeSide(Side side);
    void deleteMoves(vector <Move*> m);
    
 //   int Player::mobilityhur(Board* node, Side side);
  //  int Player::potentialMobility(Board* node, Side side);
  //  int Player::coinParity(Board* node, Side side);
  //  int Player::stablity(Board* node);
//	int Player::corners(Board* node);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
