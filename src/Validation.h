#ifndef VALIDATION_H
#define VALIDATION_H

#pragma once
#include <algorithm>
#include <functional>
#include <vector>
#include "Evaluation.h"
#include "Move.h"


class Validation {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	
/*private:
	int numRows;
	int numCols;
	int k;
	int **gameState;
	bool gravityOn;
	bool isInOrder;
	std::vector<Move> validMoves;*/

public:
	Validation();
	//Validation(int numRows, int numCols, int k, int **gameState, bool gravityOn, bool inInOrder);

	std::vector<Move> checkValidMoves(int numCols, int numRows, int k, int** gameState, bool gravityOn, bool isInOrder);
	MoveInfo buildValidTree(int numCols, int numRows, int** gameState, bool isPlayerTurn, Move tempMove);

	//int** initBoard();
	//int** copyBoard(int** tempBoard);
};

#endif //VALIDATION_H