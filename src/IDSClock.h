#ifndef IDSCLOCK_H
#define IDSCLOCK_H

#pragma once
#include <ctime>
#include "AlphaBeta.h"
#include "Move.h"


class IDSClock {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	
/*private:
	int deadline;
	int numRows;
	int numCols;
	int k;
	int maxValue;
	int minValue;
	int dp;
	bool isFirstPlayer;
	bool gravityOn;
	bool isPlayerTurn;
	MoveInfo storedMove;
	std::clock_t ct;*/

public:
	IDSClock();
	//IDSClock(int deadline, int numRows, int numCols, int k, int maxValue, int minValue, bool isFirstPlayer, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct);

	Move IDS(int numCols, int numRows, int k, int maxValue, int minValue, int deadline, int** gameState, bool gravityOn, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct);
};

#endif //IDSCLOCK_H