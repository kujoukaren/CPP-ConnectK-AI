#ifndef AISHELL_H
#define AISHELL_H

//#pragma once
#include <algorithm>
#include <ctime>
#include <limits>
#include <math.h>
//#include <random>
#include <string>
#include <vector>
//#include "AlphaBeta.h"
//#include "Evaluation.h"
//#include "GameStateChecker.h"
//#include "IDSClock.h"
//#include "MinMax.h"
#include "Move.h"
//#include "Validation.h"


// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;


private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	std::string version;
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	bool isFirstPlayer; //true if the turn is first player; false if the turn is second
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.
	Move efficientMove;


public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
	
	//Evaluation
	int evalFunc(int numCols, int numRows, int k, int** gameState, bool isFirstPlayer);
	void boardCheck(int numCols, int numRows, int k, int** listMax, int** listMin, int** gameState);
	
	//GameStateChecker
	int findAll(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int northWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int north(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int northEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int west(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int east(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int southWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int south(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int southEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	
	//Minimax
	int findMaximum(int maxValue, int minValue, int dp, int** gameState);
	int findMinimum(int maxValue, int minValue, int dp, int** gameState);
	int retrieveNumCols();
	int retrieveNumRows();
	int retrieveK();
	
	//Validation
	std::vector<Move> checkValidMoves(int** gameState, bool isInOrder);
	MoveInfo buildValidTree(int** gameState, bool isPlayerTurn, Move tempMove);
	
	//Alpha Beta
	Move alphaBetaPruning(int maxValue, int minValue, int dp, MoveInfo storedMove);
	
	//IDS
	Move IDS(int maxValue, int minValue, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct);
	Move retrieveEfficientMove();
};

#endif //AISHELL_H
