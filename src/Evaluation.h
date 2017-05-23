#ifndef EVALUATION_H
#define EVALUATION_H

#pragma once
#include <cmath>
#include <limits>
#include "GameStateChecker.h"


class Evaluation {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	
/*private:
	int numRows;
	int numCols;
	int k;
	int counterMax;
	int counterMin;
	double valueMax;
	double valueMin;
	int **listMax;
	int **listMin;
	int **gameState;
	bool isFirstPlayer;
	bool isBlocked;
	bool gravityOn;*/

public:
	Evaluation();
	//Evaluation(int numRows, int numCols, int k, int **gameState, bool isFirstPlayer, bool gravityOn);

	int evalFunc(int numCols, int numRows, int k, int** gameState, bool gravityOn, bool isFirstPlayer);
	void boardCheck(int numCols, int numRows, int k, int** listMax, int** listMin, int** gameState);

	/*void initList();
	void deleList();*/
};

#endif //EVALUATION_H