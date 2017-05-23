#ifndef GAMESTATECHECKER_H
#define GAMESTATECHECKER_H

#pragma once


class GameStateChecker {
public:
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;

/*
private:
	int row;
	int col;
	int numRows;
	int numCols;
	int k;
	int** gameState;
	bool isFirstPlayer;
*/

public:
	GameStateChecker();
	//GameStateChecker(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	
	int findAll(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int northWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int north(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int northEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int west(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int east(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int southWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int south(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
	int southEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer);
};

#endif //GAMESTATECHECKER_H