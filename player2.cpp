#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 * 
 * This is a small change
 * 
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    s = side;
    b = new Board();

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete b;
}


/*
 * Simple heuristic which computes the difference in pieces between player's side and opponent's side
 */
 
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
     Side opp;
     if (s == BLACK)
     {
		 opp = WHITE;
	 }
	 else
	 {
		 opp = BLACK;
	 } 
     b->doMove(opponentsMove, opp);
     if (! b->hasMoves(s))
     {
		 return NULL;
	 }
     for (int i = 0; i < 8; i++) 
     {
        for (int j = 0; j < 8; j++) 
        {
            Move *move = new Move(i, j);
            if (b->checkMove(move, s))
            {
				b->doMove(move,s);
				return move;
			}
			delete move;
        }
    }
    return NULL;
}
