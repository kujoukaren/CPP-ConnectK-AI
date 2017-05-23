#include "Validation.h"


Validation::Validation() {
	/*numRows = 0;
	numCols = 0;
	k = 0;
	gravityOn = false;
	isInOrder = false;*/
}

/*Validation::Validation(int numRows, int numCols, int k, int **gameState, bool gravityOn, bool isInOrder) {
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	this->gameState = gameState;
	this->gravityOn = gravityOn;
	this->isInOrder = isInOrder;
}*/

std::vector<Move> Validation::checkValidMoves(int numCols, int numRows, int k, int** gameState, bool gravityOn, bool isInOrder) {
	std::vector<Move> validMoves;
	if (gravityOn) {
		for (int col=0; col < numCols; col++) {
			for (int row=numRows-1; row >= 0; row--) {
				if (gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.col = col;
					tempMove.row = row;
					MoveInfo tempMoveInfo = buildValidTree(numCols, numRows, gameState, !isInOrder, tempMove);
					Evaluation eva;
					tempMove.evalValue = eva.evalFunc(numCols, numRows, k, tempMoveInfo.gameState, gravityOn, isInOrder);
					tempMove.gameState = tempMoveInfo.gameState;
					validMoves.push_back(tempMove);
					break;
				}
			}
		}
	}
	else {
		for(int col=0; col < numCols; col++) {
			for(int row=0; row < numRows; row++) {
				if(gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.col = col;
					tempMove.row = row;
					MoveInfo tempMoveInfo = buildValidTree(numCols, numRows, gameState, !isInOrder, tempMove);
					Evaluation eva;
					tempMove.evalValue = eva.evalFunc(numCols, numRows, k, tempMoveInfo.gameState, gravityOn, isInOrder);
					tempMove.gameState = tempMoveInfo.gameState;
					tempMove.storedMove = tempMoveInfo;
					validMoves.push_back(tempMove);
				}
			}
		}
	}
	
	if(isInOrder) {
		std::stable_sort(validMoves.begin(), validMoves.end());
	}
	else {
		std::stable_sort(validMoves.begin(), validMoves.end(), std::greater<Move>());
		
	}

	return validMoves;

	/*if (gravityOn) {
		for (int col = 0; col < numCols; col++) {
			for (int row = numRows - 1; row >= 0; row--) {
				if (gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.row = row;
					tempMove.col = col;
					MoveInfo tempMoveInfo = buildValidTree(tempMove);
					tempMove.storedMove = tempMoveInfo;
					tempMove.gameState = tempMoveInfo.gameState;
					Evaluation eva(numRows, numCols, k, tempMoveInfo.gameState, isInOrder, gravityOn);
					tempMove.evalValue = eva.evalFunc();
					validMoves.push_back(tempMove);
				}
				break;
			}
		}
	}
	else {
		for (int row = 0; row < numRows; row++) {
			for (int col = 0; col < numCols; col++) {
				if (gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.row = row;
					tempMove.col = col;
					MoveInfo tempMoveInfo = buildValidTree(tempMove);
					tempMove.storedMove = tempMoveInfo;
					tempMove.gameState = tempMoveInfo.gameState;
					Evaluation eva(numRows, numCols, k, tempMoveInfo.gameState, isInOrder, gravityOn);
					tempMove.evalValue = eva.evalFunc();
					validMoves.push_back(tempMove);
				}
			}
		}
	}

	if (!isInOrder) {
		std::stable_sort(validMoves.begin(), validMoves.end(), std::greater<Move>());
	}
	else {
		std::stable_sort(validMoves.begin(), validMoves.end());
	}

	return validMoves;*/
}

MoveInfo Validation::buildValidTree(int numCols, int numRows, int** gameState, bool isPlayerTurn, Move tempMove) {
	int** tempBoard = new int*[numCols];
	for (int col=0; col < numCols; col++) {
		tempBoard[col] = new int[numRows];
	}

	for (int col=0; col < numCols; col++){
		for (int row=0; row < numRows; row++){
			tempBoard[col][row] = gameState[col][row];
		}
	}

	if (isPlayerTurn) {
		tempBoard[tempMove.col][tempMove.row] = AI_PIECE;
	}
	else {
		tempBoard[tempMove.col][tempMove.row] = HUMAN_PIECE;
	}
	

	MoveInfo tempMoveInfo;
	tempMoveInfo.col = tempMove.col;
	tempMoveInfo.row = tempMove.row;
	tempMoveInfo.gameState = tempBoard;
	
	return tempMoveInfo;

	/*int** tempBoard = initBoard();

	if (isInOrder) {
		tempBoard[tempMove.col][tempMove.row] = HUMAN_PIECE;
	}
	else {
		tempBoard[tempMove.col][tempMove.row] = AI_PIECE;
	}

	MoveInfo tempMoveInfo;
	tempMoveInfo.col = tempMove.col;
	tempMoveInfo.row = tempMove.row;
	tempMoveInfo.gameState = tempBoard;

	return tempMoveInfo;*/
}

/*int** Validation::initBoard() {
	int** tempBoard = new int*[numCols];
	for (int i = 0; i < numCols; i++) {
		tempBoard[i] = new int[numRows];
	}
	copyBoard(tempBoard);
	return tempBoard;
}

int** Validation::copyBoard(int** tempBoard) {
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			tempBoard[c][r] = gameState[c][r];
		}
	}
	return tempBoard;
}*/