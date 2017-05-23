#include "MinMax.h"


MinMax::MinMax() {
	/*numRows = 0;
	numCols = 0;
	k = 0;
	isFirstPlayer = false;
	gravityOn = false;*/
}

/*MinMax::MinMax(int numRows, int numCols, int k, bool isFirstPlayer, bool gravityOn) {
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	this->isFirstPlayer = isFirstPlayer;
	this->gravityOn = gravityOn;
}*/

int MinMax::findMaximum(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int **gameState, bool gravityOn) {
	if (dp == 0) {
		Evaluation eva;
		return eva.evalFunc(numCols, numRows, k, gameState, gravityOn, true);
	}

	int alpha = std::numeric_limits<int>::min();
	Validation v;
	std::vector<Move> validMoves = v.checkValidMoves(numCols, numRows, k, gameState, gravityOn, false);
	for (int count = 0, index = 0; index < validMoves.size(); count++, index++)
	{
		int beta = findMinimum(numCols, numRows, k, maxValue, minValue, dp-1, validMoves[index].gameState, gravityOn);
		alpha = std::max(alpha, beta);

		if (alpha >= minValue)
		{
			return alpha;
		}
		maxValue = std::max(maxValue, alpha);
	}
	return alpha;

	/*int alpha = std::numeric_limits<int>::min();
	if (dp != 0) {
		Validation v(numRows, numCols, k, gameState, gravityOn, false);
		std::vector<Move> validMoves = v.checkValidMoves();
		for (int count = 0, index = 0; index < validMoves.size(); count++, index++) {
			int beta = findMinimum(maxValue, minValue, dp-1, validMoves[index].gameState);
			alpha = std::max(alpha, beta);
			
			if (minValue <= alpha) {
				return alpha;
			}

			maxValue = std::max(maxValue, alpha);
		}
	}
	else {
		Evaluation eva(numRows, numCols, k, gameState, isFirstPlayer, gravityOn);
		return eva.evalFunc();
	}
	return alpha;*/
}

int MinMax::findMinimum(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int **gameState, bool gravityOn) {
	if (dp == 0) {
		Evaluation eva;
		return eva.evalFunc(numCols, numRows, k, gameState, gravityOn, false);
	}

	int beta = std::numeric_limits<int>::max();
	Validation v;
	std::vector<Move> validMoves = v.checkValidMoves(numCols, numRows, k, gameState, gravityOn, true);
	for (int count = 0, index = 0; index < validMoves.size(); count++, index++) {
		int alpha = findMaximum(numCols, numRows, k, maxValue, minValue, dp-1, validMoves[index].gameState, gravityOn);
		beta = std::min(beta, alpha);

		if (beta <= maxValue) {
			return beta;
		}
		minValue = std::min(minValue, beta);

	}
	return beta;

	/*int beta = std::numeric_limits<int>::max();
	if (dp != 0) {
		Validation v(numRows, numCols, k, gameState, gravityOn, true);
		std::vector<Move> validMoves = v.checkValidMoves();
		for (int count = 0, index = 0; index < validMoves.size(); count++, index++) {
			int alpha = findMaximum(maxValue, minValue, dp-1, validMoves[index].gameState);
			beta = std::min(beta, alpha);

			if (maxValue >= beta) {
				return maxValue;
			}

			minValue = std::min(minValue, beta);
		}
	}
	else {
		Evaluation eva(numRows, numCols, k, gameState, isFirstPlayer, gravityOn);
		return eva.evalFunc();
	}
	return beta;*/
}