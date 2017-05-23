#ifndef MINMAX_H
#define MINMAX_H

#pragma once
#include <algorithm>
#include <limits>
#include <vector>
#include "Evaluation.h"
#include "Move.h"
#include "Validation.h"


class MinMax {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;

/*private:
	int numRows;
	int numCols;
	int k;
	bool isFirstPlayer;
	bool gravityOn;*/

public:
	MinMax();
	//MinMax(int numRows, int numCols, int k, bool isFirstPlayer, bool gravityOn);

	int findMaximum(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int** gameState, bool gravityOn);
	int findMinimum(int numCols, int numRows, int k, int maxValue, int minValue, int dp, int** gameState, bool gravityOn);
};

#endif //MINMAX_H