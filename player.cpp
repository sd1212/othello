#include "player.h"
#include <cstdio>
#include <math.h> 
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
 * Simple heuristic which weights corners and edges highly
 */
 int Player::simpleScore(Move *yourMove, Side mover, Board *cop)
 {
	 Side opp;
	 double bonus = 1;
	 if (yourMove->x == 0 || yourMove->x == 7)
	 {
		 bonus = bonus + 1;
	 }
	 if (yourMove -> y == 0 || yourMove->y == 7)
	 {
		 bonus = bonus + 1;
     }
     if ((yourMove->x == 1 && yourMove->y == 0) || (yourMove->x == 1 && yourMove->y == 0) )
     {
		 bonus = bonus - 1;
	 }
	 if ((yourMove->x == 1 && yourMove->y == 7) || (yourMove->x == 0 && yourMove->y == 6) )
     {
		 bonus = bonus - 1;
	 }
	 if ((yourMove->y == 1 && yourMove->x == 7) || (yourMove->y == 0 && yourMove->x == 6) )
     {
		 bonus = bonus - 1;
	 }
	 if ((yourMove->y == 6 && yourMove->x == 7) || (yourMove->y == 7 && yourMove->x == 6) )
     {
		 bonus = bonus - 1;
	 }
	 if ((yourMove->x == 6 && yourMove->y ==6) || (yourMove->x == 1 && yourMove->y ==1))
	 {
		 bonus = bonus - 2;
	 }
	 if ((yourMove->x == 1 && yourMove->y ==6) || (yourMove->x == 6 && yourMove->y ==6))
	 {
		 bonus = bonus - 2;
	 }      
	 if (mover == BLACK)
     {
		 opp = WHITE;
	 }
	 else
	 {
		 opp = BLACK;
	 }
	 int score = bonus + (cop->count(mover) - cop->count(opp));
	 return score;
}

/*
 * A more advanced miniMax that uses the hueristicFunction
 */
 int Player::miniMaxScore2(Move *yourMove, Side mover)
 {
	 Side opp;
	 if (mover == BLACK)
     {
		 opp = WHITE;
	 }
	 else
	 {
		 opp = BLACK;
	 }
	 Board *cop1 = b->copy();
	 cop1->doMove(yourMove, mover);
	 int minscore = cop1->count(mover) - cop1->count(opp);
	 for (int i = 0; i < 8; i++)
	 {
		 for (int j = 0; j < 8; j++)
		 {
			Board* cop = cop1->copy();
			Move *cand = new Move(i,j);
			if (cop->checkMove(cand, opp))
			{
				int tempscore = simpleScore(cand,opp,cop);
				if (tempscore < minscore)
				{
					minscore = tempscore;
				}
			}
			delete cand;
		}
	}
	return minscore;
}

/*
 * Checks heuristic two moves in the future
 */
 int Player::miniMaxScore(Move *yourMove, Side mover)
 {
	 Side opp;
	 if (mover == BLACK)
     {
		 opp = WHITE;
	 }
	 else
	 {
		 opp = BLACK;
	 }
	 Board *cop1 = b->copy();
	 cop1->doMove(yourMove, mover);
	 int minscore = cop1->count(mover) - cop1->count(opp);
	 for (int i = 0; i < 8; i++)
	 {
		 for (int j = 0; j < 8; j++)
		 {
			Board* cop = cop1->copy();
			Move *cand = new Move(i,j);
			if (cop->checkMove(cand, opp))
			{
				cop ->doMove(cand, opp);
				int tempscore = cop->count(mover) - cop->count(opp);
				if (tempscore < minscore)
				{
					minscore = tempscore;
				}
			}
			delete cand;
		}
	}
	return minscore;
}
 
 
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
     int maxscore = -65;
     Move *maxmove = NULL;
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
				int tempscore;
				if (testingMinimax)
				{
					tempscore = miniMaxScore(move, s);
				}
				else
				{
					tempscore = miniMaxScore2(move, s);
				}
				if (tempscore > maxscore)
				{
					delete maxmove;
					maxscore = tempscore;
					maxmove = new Move(i,j);
				}
			}
			delete move;
        }
    }
    b->doMove(maxmove, s);
    return maxmove;
}
