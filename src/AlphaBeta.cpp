#include "AlphaBeta.h"


AlphaBeta::AlphaBeta() {
	/*numRows = 0;
	numCols = 0;
	k = 0;
	maxValue = 0;
	minValue = 0;
	dp = 0;
	efficientValue = 0;
	isFirstPlayer = false;
	gravityOn = false;
	isPlayerTurn = false;*/
}

/*AlphaBeta::AlphaBeta(int numRows, int numCols, int k, int maxValue, int minValue, int dp, bool isFirstPlayer, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove) {
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	this->maxValue = maxValue;
	this->minValue = minValue;
	this->dp = dp;
	this->efficientValue = std::numeric_limits<int>::min();
	this->isFirstPlayer = isFirstPlayer;
	this->gravityOn = gravityOn;
	this->isPlayerTurn = isPlayerTurn;
	this->storedMove = storedMove;
}*/

Move AlphaBeta::alphaBetaPruning(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int** gameState, bool gravityOn, MoveInfo storedMove) {
	int efficientValue = std::numeric_limits<int>::min();
	Move efficientMove;
	Validation v;
	std::vector<Move> validMoves = v.checkValidMoves(numCols, numRows, k, storedMove.gameState, gravityOn, false);
	for (int index = 0; index < validMoves.size(); index++)
	{
		MinMax mm;
		int alpha = mm.findMaximum(numCols, numRows, k, maxValue, minValue, dp, validMoves[index].gameState, gravityOn);
		if (alpha >= efficientValue)
		{
			efficientValue = alpha;
			efficientMove.col = validMoves[index].col;
			efficientMove.row = validMoves[index].row;
		}
	}
	return efficientMove;

	/*Validation v(numRows, numCols, k, storedMove.gameState, gravityOn, false);
	validMoves = v.checkValidMoves();

	for (int index = 0; index < validMoves.size(); index++) {
		MinMax mm(numRows, numCols, k, isFirstPlayer, gravityOn);
		int alpha = mm.findMaximum(maxValue, minValue, dp, validMoves[index].gameState);

		if(efficientValue <= alpha) {
			efficientValue = alpha;
			efficientMove.row = validMoves[index].row;
			efficientMove.col = validMoves[index].col;
		}
	}

	return efficientMove;*/
}