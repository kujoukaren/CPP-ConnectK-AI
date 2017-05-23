#include "IDSClock.h"


IDSClock::IDSClock() {
	/*deadline = 0;
	numRows = 0;
	numCols = 0;
	k = 0;
	maxValue = 0;
	minValue = 0;
	dp = 0;
	isFirstPlayer = false;
	gravityOn = false;
	isPlayerTurn = false;*/
	//std::clock_t = std::clock();
}

/*IDSClock::IDSClock(int deadline, int numRows, int numCols, int k, int maxValue, int minValue, bool isFirstPlayer, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct) {
	this->deadline = deadline;
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	this->maxValue = maxValue;
	this->minValue = minValue;
	this->isFirstPlayer = isFirstPlayer;
	this->gravityOn = gravityOn;
	this->isPlayerTurn = isPlayerTurn;
	this->storedMove = storedMove;
	this->ct = ct;
}*/

Move IDSClock::IDS(int numCols, int numRows, int k, int maxValue, int minValue, int deadline, int** gameState, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct) {
	int dp = 2;
	Move efficientMove;

	for(; ((std::clock() -  ct)/double(CLOCKS_PER_SEC) * 1000) < deadline; ct = std::clock()) {
		AlphaBeta ab;
		efficientMove = ab.alphaBetaPruning(numCols, numRows, k, maxValue, minValue, dp, gameState, gravityOn, storedMove);
		dp++;
	}
	return efficientMove;

	/*dp = 2;
	Move efficientMove;

	for(; ((std::clock() -  ct)/double(CLOCKS_PER_SEC) * 1000) < deadline; ct = std::clock()) {
		AlphaBeta ab(numRows, numCols, k, maxValue, minValue, dp, isFirstPlayer, gravityOn, isPlayerTurn, storedMove);
		efficientMove = ab.alphaBetaPruning();
		dp++;
	}
	return efficientMove;*/
}