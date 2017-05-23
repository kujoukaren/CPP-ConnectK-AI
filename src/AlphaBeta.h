#ifndef ALPHABETA_H
#define ALPHABETA_H

#pragma once
#include <limits>
#include <vector>
#include "MinMax.h"
#include "Move.h"
#include "Validation.h"

class AlphaBeta {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	
/*private:
	int numRows;
	int numCols;
	int k;
	int maxValue;
	int minValue;
	int dp;
	int efficientValue;
	bool isFirstPlayer;
	bool gravityOn;
	bool isPlayerTurn;
	Move efficientMove;
	MoveInfo storedMove;
	std::vector<Move> validMoves;*/

public:
	AlphaBeta();
	//AlphaBeta(int numRows, int numCols, int k, int maxValue, int minValue, int dp, bool isFirstPlayer, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove);

	Move alphaBetaPruning(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int** gameState, bool gravityOn, MoveInfo storedMove);
};

#endif //ALPHABETA_H