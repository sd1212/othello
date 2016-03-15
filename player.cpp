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
 int Player::simpleScore(Side mover, Board *cop, Move* yourMove)
 {
	 Side opp = getOppositeSide(mover);
	 int numwins = 0;
	 for (int i = 0; i < 25; i++)
	 {
		 Board* cop2 = cop->copy();
		 Side currentPlayer = mover;
		 while (! cop2->isDone())
		 {
			 vector <Move*> m = getPossibleMoves(cop2, currentPlayer);
			 int n = m.size();
			 if (n == 0)
			 {
				 currentPlayer = getOppositeSide(currentPlayer);
				 continue;
			 }
			 int index = rand() % n;
			 cop2->doMove(m[index], currentPlayer);
			 currentPlayer = getOppositeSide(currentPlayer);
			 deleteMoves(m);
		}
		if (cop2->count(mover) - cop2->count(opp) > 0)
		{
			numwins++;
		}
		delete cop2;
	}
	return numwins;
}

int Player::alphaBetaPruning(int depth, Board* node, int alpha, int beta, Side side, Move* move)
{
	Side opp = getOppositeSide(side);
	if (depth == 0)
	{
		int score = simpleScore(side, node, move);
		delete node;
		return score;
	}
	vector<Move* > m = getPossibleMoves(node, side);
	for (unsigned int i = 0; i < m.size(); i++)
	{
		Board* child = node->copy();
		child->doMove(m[i], side);
		int score = -1*alphaBetaPruning(depth -1, child, -beta, -alpha, opp, m[i]);
		if (score > alpha)
		{
			alpha = score;
		}
		if (alpha >= beta)
		{
			break;
		}
	}
	if (m.empty())
	{
		Board* child = node->copy();
		int score = -1*alphaBetaPruning(depth -1, child, -beta, -alpha, opp, NULL);
		if (score > alpha)
		{
			alpha = score;
		}
	}
	deleteMoves(m);
	delete node;
	return alpha;
}
void Player::deleteMoves(vector <Move*> m)
{
	for (unsigned int i = 0; i < m.size(); i++)
	{
		delete m[i];
	}
}
vector<Move*> Player::getPossibleMoves(Board* node, Side side)
{
	vector <Move*> m;
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			Move *move = new Move(i, j);
			if (node->checkMove(move, side))
			{
				m.push_back(move);
			}
			else
			{
				delete move;
			}
		}
	}
	return m;
}

Side Player::getOppositeSide(Side side)
{
	Side opp;
	if (side == BLACK)
     {
		 opp = WHITE;
	 }
	 else
	 {
		 opp = BLACK;
	 }
	 return opp;
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
     Side opp = getOppositeSide(s);
     b->doMove(opponentsMove,opp);
     if (! b->hasMoves(s))
     {
		 return NULL;
	 }
	 vector<Move*> m = getPossibleMoves(b,s);
	 unsigned int maxindex = 0;
	 int alpha = -100;
	 int beta = 100;
	 for (unsigned int i = 0; i < m.size(); i++)
	 {
		 Board* node = b->copy();
		 node->doMove(m[i], s);
		 int score = -1*alphaBetaPruning(3, node, -beta, -alpha, opp, m[i]);
		 if (score > alpha)
		 {
			 alpha = score;
			 maxindex = i;
		 }
	 }
	 b->doMove(m[maxindex],s);
	 Move* maxmove = m[maxindex];
	 Move* selectedMove = new Move(maxmove->x, maxmove->y);
	 deleteMoves(m);
	 return selectedMove;
}
