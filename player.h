#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board *b = NULL;
    Side s;
    
    Move *doMove(Move *opponentsMove, int msLeft);
    int simpleScore(Move *yourMove, Side mover, Board* cop);
    int miniMaxScore(Move *yourMove, Side mover);
    int miniMaxScore2(Move *yourMove, Side mover);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
