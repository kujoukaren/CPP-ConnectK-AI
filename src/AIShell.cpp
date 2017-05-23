#include "AIShell.h"
#include <iostream>


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->version="ver6";
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	//this->tally=0;
	this->gravityOn=gravityOn;
	this->isFirstPlayer=false;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
	
	

	if (version == "ver0") { //"ver0" is the version without AI
		//this will move to the left-most column possible.
		for (int col = 0; col<numCols; col++){
			for (int row = 0; row<numRows; row++){
				if (gameState[col][row] == NO_PIECE){
					Move m(col, row);
					return m;
				}
			}
		}
	}
	else if (version == "ver1") { //"ver1" is the version of random move
		/*bool isEmptied = true;
		std::random_device rdRow;
		std::random_device rdCol;
		std::uniform_int_distribution<int> distRow(0, numRows);
		std::uniform_int_distribution<int> distCol(0, numCols);
		while (isEmptied) {
			int rRow = distRow(rdRow);
			int rCol = distCol(rdCol);
			if (gameState[rCol][rRow] == NO_PIECE) {
				isEmptied = false;
				Move m(rCol, rRow);
				return m;
			}
		}*/
		Move m(0,0);
		return m;
	}
	else if (version == "ver2") { //"ver2" is the version with evaluation function
		Move m(0, 0);
		return m;
	}
	else if (version == "ver3") { //"ver3" is the version with Min-Max
		Move m(0, 0);
		return m;
	}
	else if (version == "ver4") { //"ver4" is the version with Alpha-Beta
		Move m(0, 0);
		return m;
	}
	else if (version == "ver5") { //"ver5" is the version with IDS
		Move m(0, 0);
		return m;
	}
	else if (version == "ver6") { //"ver6" is the final version
		//int i = std::numeric_limits<int>::min();
		//int a = i + 1;
		//int b = a + 570;
		//std::cout << b << std::endl;
		
		Move efficientMove;
		int efficientCol = 0;
		int efficientRow = 0;
		int efficientValue = -1000000;

		MoveInfo storedMove;
		storedMove.col = lastMove.col;
		storedMove.row = lastMove.row;
		storedMove.gameState = gameState;

		if(gravityOn) {
	    	for (int c1=0; c1 < numCols; c1++) {
				for (int r1=0; r1 < numRows; r1++) {			
					if (gameState[c1][r1] == NO_PIECE){
						int** tempBoard = new int*[numCols];
						for(int c2=0; c2 < numCols; c2++) {
							tempBoard[c2] = new int[numRows];
							for(int r2=0; r2 < numRows; r2++) {
								tempBoard[c2][r2] = gameState[c2][r2];
							}
						}
						tempBoard[c1][r1] = 1;
						//Evaluation eva;
						int tempValue = evalFunc(numCols, numRows, k, tempBoard, true);
						if (tempValue > efficientValue) {
							efficientCol = c1;
							efficientRow = r1;
							efficientValue = tempValue;
						}

						for(int c3=0; c3 < numCols; c3++) {
							delete[] tempBoard[c3];
						}
						delete[] tempBoard;
					}
				}
			}
			Move pickedMove(efficientCol, efficientRow);
			return pickedMove;
		}
		else {	
			//AlphaBeta ab;
			efficientMove = alphaBetaPruning(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 2, storedMove);
		}

		return efficientMove;

		/*Move efficientMove;
		int efficientRow = 0;
		int efficientCol = 0;
		int efficientValue = -1000000;
		MoveInfo temp;
		temp.col = lastMove.col;
		temp.row = lastMove.row;
		temp.gameState = gameState;
		if (!gravityOn) {
			AlphaBeta ab(numRows, numCols, k, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 2, isFirstPlayer, gravityOn, true, temp);
			efficientMove = ab.alphaBetaPruning();
		}
		else {
			for(int c = 0; c < numCols; c++) {
				for(int r = 0; r < numRows; r++) {
					if (gameState[c][r] == NO_PIECE) {
						int** tempBoard = new int*[numCols];
						for (int c2 = 0; c2 < numCols; c2++) {
							tempBoard[c2] = new int [numRows];
							for (int r2 = 0; r2 < numRows; r2++) {
								tempBoard[c2][r2] = gameState[c2][r2];
							}
						}
						
						tempBoard[c][r] = AI_PIECE;
						
						Evaluation eva(numRows, numCols, k, gameState, isFirstPlayer, gravityOn);
						int evalValue = eva.evalFunc();
						if (evalValue > efficientValue) {
							efficientValue = evalValue;
							efficientCol = c;
							efficientRow = r;
						}

						for (int d = 0; d < numCols; d++) {
							delete[] tempBoard[d];
						}
						delete[] tempBoard;
					}
				}
			}
			Move eMove(efficientCol, efficientRow);
			return eMove;
		}*/
	}
	Move m(0, 0);
	return m;
}

//Evaluation
int AIShell::evalFunc(int numCols, int numRows, int k, int** gameState, bool isFirstPlayer) {
	double valueMax = 0;
	double valueMin = 0;
	
	int** listMax = new int*[4];
	int** listMin = new int*[4];

	for(int col = 0; col < 4; col++) {
		listMax[col] = new int[k+1];
		listMin[col] = new int[k+1];
	}

	for (int col=0; col < 4; col++) {
		for (int row=0; row < k+1; row++) {
			listMax[col][row] = 0;
			listMin[col][row] = 0;
		}
	}

	boardCheck(numCols, numRows, k, listMax, listMin, gameState);
		
	for (int col=0; col < 4; col++) {
		for (int row=0; row < k+1; row++) {
			valueMax += (double)row * listMax[col][row] * pow(5, row);
			valueMin -= (double)row * listMin[col][row] * pow(5, row);
		}
	}
	
	for(int col=0; col < 4; col++) {
		if(listMin[col][k-1] != 0) {
			valueMin =  std::numeric_limits<int>::min()+3;
		}
	}

	for(int col=0; col < 4; col++) {
		if(listMin[col][k-2] != 0) {
			valueMin = std::numeric_limits<int>::min()+2;
		}
	}
	
	for(int col=0; col < 4; col++) {
		if(listMin[col][k] != 0) {
			valueMin = std::numeric_limits<int>::min()+1;
		}
	}

	for(int col=0; col < 4; col++) {
		if(listMax[col][k] != 0) {
			valueMax = std::numeric_limits<int>::max()-1;
		}
	}

	for(int col=0; col < 4; col++) {
		delete[] listMax[col];
		delete[] listMin[col];
	}
	delete[] listMax;
	delete[] listMin;

	if(gravityOn) {
		int valueMinMax = 0;
		for (int col=0; col < numCols; col++) {
			for (int row=0; row < numRows; row++) {
				valueMinMax += findAll(col, numCols, row, numRows, k, gameState, true);
			}
		}
		return valueMinMax;	
	}
	else {
		if(isFirstPlayer) {
			return valueMin-valueMax;

		}
		else {
			return -valueMin-valueMax;
		}
	}
}

void AIShell::boardCheck(int numCols, int numRows, int k, int** listMax, int** listMin, int** gameState) {
	int counterMax = 0;
	int counterMin = 0;
	bool isBlocked = false;
	for (int col=0; col <= numCols-k; col++) {
		for (int row=0; row < numRows; row++) {
			for (int len=0; len < k; len++) {
				if (gameState[col+len][row] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col+len][row] == HUMAN_PIECE) {
					counterMin += 1;
				}

			}

			if (counterMax > 0 && counterMin > 0) {
				isBlocked = true;
			}

			if (!isBlocked) {
				listMax[0][counterMax] += 1;
				listMin[0][counterMin] += 1;
			}
			counterMax = 0;
			counterMin = 0;
			isBlocked = false;
		}
	}

	for (int col=0; col < numCols; col++) {
		for (int row=0; row <= numRows-k; row++) {
			for (int len=0; len < k; len++) {
				if (gameState[col][row+len] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col][row+len] == HUMAN_PIECE) {
					counterMin += 1;
				}
				
			}

			if (counterMax > 0 && counterMin > 0) {
				isBlocked = true;
			}

			if (!isBlocked) {
				listMax[1][counterMax] += 1;
				listMin[1][counterMin] += 1;
			}
			counterMax = 0;
			counterMin = 0;
			isBlocked = false;
		}
	}

	for (int col=0; col < numCols-k+1; col++) {
		for (int row=0; row < numRows-k+1; row++) {
			for (int len=0; len < k; len++) {
				if (gameState[col+len][row+len] == AI_PIECE) {
					counterMin += 1;
				}
				else if (gameState[col+len][row+len] == HUMAN_PIECE) {
					counterMax += 1;
				}
			}

			if (counterMax > 0 && counterMin > 0) {
				isBlocked = true;
			}

			if (!isBlocked) {
				listMax[2][counterMax] += 1;
				listMin[2][counterMin] += 1;
			}
			counterMax = 0;
			counterMin = 0;
			isBlocked = false;
		}
	}

	for (int col=numCols-1; col >= k-1; col--) {
		for (int row=numRows-k; row >= 0; row--) {
			for (int len=0; len < k; len++) {
				if (gameState[col-len][row+len] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col-len][row+len] == HUMAN_PIECE) {
					counterMin += 1;
				}
			}

			if (counterMax > 0 && counterMin > 0) {
				isBlocked = true;
			}

			if (!isBlocked) {
				listMax[3][counterMax] += 1;
				listMin[3][counterMin] += 1;
			}
			counterMax = 0;
			counterMin = 0;
			isBlocked = false;
		}
	}
}
	
//GameStateChecker
int AIShell::findAll(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	int n = north(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int s = south(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int w = west(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int e = east(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int nw = northWest(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int ne = northEast(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int sw = southWest(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int se = southEast(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int allDirections = n + s + w + e + nw + ne + sw + se;
	return allDirections;
}
int AIShell::north(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row-k+1 < 0) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col][row-len] != PLAYER && gameState[col][row-len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col][row-len] == PLAYER) {
					northValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (northValue == k-2 && PLAYER == -1) {
					northValue = 300;
				}
				else if (northValue == k-1 && PLAYER == -1) {
					northValue = 3000;
				}
				else if (northValue == k-1 && PLAYER == 1) {
					northValue = 300;
				}
				else if (northValue == k) {
					northValue = 10000;
				}
			}
			else {
				if (northValue == k-2 && PLAYER == 1) {
					northValue = 300;
				}
				else if (northValue == k-1 && PLAYER == 1) {
					northValue = 3000;
				}
				else if (northValue == k-1 && PLAYER == -1) {
					northValue = 300;
				}
				else if (northValue == k) {
					northValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return northValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -northValue;
			}
		}
	}
	return 0;
}

int AIShell::south(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row+k > numRows) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col][row+len] != PLAYER && gameState[col][row+len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col][row+len] == PLAYER) {
					southValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (southValue == k-2 && PLAYER == -1) {
					southValue = 300;
				}
				else if (southValue == k-1 && PLAYER == -1) {
					southValue = 3000;
				}
				else if (southValue == k-1 && PLAYER == 1) {
					southValue = 300;
				}
				else if (southValue == k) {
					southValue = 10000;
				}
			}
			else {
				if (southValue == k-2 && PLAYER == 1) {
					southValue = 300;
				}
				else if (southValue == k-1 && PLAYER == 1) {
					southValue = 3000;
				}
				else if (southValue == k-1 && PLAYER == -1) {
					southValue = 300;
				}
				else if (southValue == k) {
					southValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return southValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -southValue;
			}
		}
	}
	return 0;
}

int AIShell::west(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int westValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col-len][row] != PLAYER && gameState[col-len][row] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-len][row] == PLAYER) {
					westValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (westValue == k-2 && PLAYER == -1) {
					westValue = 300;
				}
				else if (westValue == k-1 && PLAYER == -1) {
					westValue = 3000;
				}
				else if (westValue == k-1 && PLAYER == 1) {
					westValue = 300;
				}
				else if (westValue == k) {
					westValue = 10000;
				}
			}
			else {
				if (westValue == k-2 && PLAYER == 1) {
					westValue = 300;
				}
				else if (westValue == k-1 && PLAYER == 1) {
					westValue = 3000;
				}
				else if (westValue == k-1 && PLAYER == -1) {
					westValue = 300;
				}
				else if (westValue == k) {
					westValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return westValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -westValue;
			}
		}
	}
	return 0;
}

int AIShell::east(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int eastValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col+k > numCols) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col+len][row] != PLAYER && gameState[col+len][row] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+len][row] == PLAYER) {
					eastValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (eastValue == k-2 && PLAYER == -1) {
					eastValue = 300;
				}
				else if (eastValue == k-1 && PLAYER == -1) {
					eastValue = 1000;
				}
				else if (eastValue == k-1 && PLAYER == 1) {
					eastValue = 300;
				}
				else if (eastValue == k) {
					eastValue = 10000;
				}
			}
			else {
				if (eastValue == k-2 && PLAYER == 1) {
					eastValue = 300;
				}
				else if (eastValue == k-1 && PLAYER == 1) {
					eastValue = 1000;
				}
				else if (eastValue == k-1 && PLAYER == -1) {
					eastValue = 300;
				}
				else if (eastValue == k) {
					eastValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return eastValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -eastValue;
			}
		}
	}
	return 0;
}

int AIShell::northWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northWestValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0 || row-k+1 < 0) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col-len][row-len] != PLAYER && gameState[col-len][row-len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-len][row-len] == PLAYER) {
					northWestValue += 1;
				}
			}
			if (isFirstPlayer) {
                if (northWestValue == k-2 && PLAYER == -1) {
					northWestValue = 300;
				}
				else if (northWestValue == k-1 && PLAYER == -1) {
					northWestValue = 3000;
				}
				else if (northWestValue == k-1 && PLAYER == 1) {
			         	northWestValue = 300;
				}
				else if (northWestValue == k) {
					northWestValue = 10000;
				}
			}
			else {
				if (northWestValue == k-2 && PLAYER == 1) {
					northWestValue = 300;
				}
				else if (northWestValue == k-1 && PLAYER == 1) {
					northWestValue = 3000;
				}
				else if (northWestValue == k-1 && PLAYER == -1) {
					northWestValue = 300;
				}
				else if (northWestValue == k) {
					northWestValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return northWestValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -northWestValue;
			}
		}
	}
	return 0;
}

int AIShell::northEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northEastValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row-k+1 < 0 || col+k > numCols) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col+len][row-len] != PLAYER && gameState[col+len][row-len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+len][row-len] == PLAYER) {
					northEastValue += 1;
				}
			}
		    if (isFirstPlayer) {
				if (northEastValue == k-2 && PLAYER == -1) {
					northEastValue = 300;
				}
				else if (northEastValue == k-1 && PLAYER == -1) {
					northEastValue =3000;
				}
				else if (northEastValue == k-1 && PLAYER == 1) {
				     northEastValue = 300;
				}
				else if (northEastValue == k) {
					northEastValue = 10000;
				}
			}
			else {
				if (northEastValue == k-2 && PLAYER == 1) {
					northEastValue = 300;
				}
				else if (northEastValue == k-1 && PLAYER == 1) {
					northEastValue = 3000;
				}
				else if (northEastValue == k-1 && PLAYER == -1) {
					northEastValue = 300;
				}
				else if (northEastValue == k) {
					northEastValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return northEastValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -northEastValue;
			}
		}
	}
	return 0;
}

int AIShell::southWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southWestValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0 || row+k > numRows) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col-len][row+len] != PLAYER && gameState[col-len][row+len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-len][row-len] == PLAYER) {
					southWestValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (southWestValue == k-2 && PLAYER == -1) {
					southWestValue = 300;
				}
				else if (southWestValue == k-1 && PLAYER == -1) {
					southWestValue = 3000;
				}
				else if (southWestValue == k-1 && PLAYER == 1) {
					southWestValue = 300;
				}
				else if (southWestValue == k) {
					southWestValue = 10000;
				}
			}
			else {
				if (southWestValue == k-2 && PLAYER == 1) {
					southWestValue = 300;
				}
				else if (southWestValue == k-1 && PLAYER == 1) {
					southWestValue = 3000;
				}
				else if (southWestValue == k-1 && PLAYER == -1) {
					southWestValue = 300;
				}
				else if (southWestValue == k) {
					southWestValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {

				return southWestValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -southWestValue;
			}
		}
	}
	return 0;
}

int AIShell::southEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southEastValue = 0;
	if (PLAYER != NO_PIECE) {
		if ((col+k > numCols) || (row+k > numRows)) {
			return 0;
		}
		else {
			for (int len=0; len < k; len++) {
				if (gameState[col+len][row+len] != PLAYER && gameState[col+len][row+len] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+len][row+len] == PLAYER) {
					southEastValue += 1;
				}
			}
			if (isFirstPlayer) {
				if (southEastValue == k-2 && PLAYER == -1){
					southEastValue = 300;
				}
				else if (southEastValue == k-1 && PLAYER == -1) {
					southEastValue = 3000;
				}
				else if (southEastValue == k-1 && PLAYER == 1) {
					southEastValue = 300;
				}
				else if (southEastValue == k) {
					southEastValue = 10000;
				}
			}
			else {
				if (southEastValue == k-2 && PLAYER == 1) {
					southEastValue = 300;
				}
				else if (southEastValue == k-1 && PLAYER == 1) {
					southEastValue = 3000;
				}
				else if (southEastValue == k-1 && PLAYER == -1) {
					southEastValue = 300;
				}
				else if (southEastValue == k) {
					southEastValue = 10000;
				}
			}
			if (PLAYER == AI_PIECE) {
				return southEastValue;
			}
			else if (PLAYER == HUMAN_PIECE) {
				return -southEastValue;
			}
		}
	}
	return 0;
}
	
//Minimax
int AIShell::findMaximum(int maxValue, int minValue, int dp, int** gameState) {
	if (dp == 0) {
		return evalFunc(retrieveNumCols(), retrieveNumRows(), retrieveK(), gameState, true);
	}

	int alpha = std::numeric_limits<int>::min();
	std::vector<Move> validMoves = checkValidMoves(gameState, false);
	for (int i = 0; i < validMoves.size(); i++)
	{
		int beta = findMinimum(maxValue, minValue, dp-1, validMoves[i].gameState);
		alpha = std::max(alpha, beta);

		if (alpha >= minValue) {
			return alpha;
		}
		maxValue = std::max(maxValue, alpha);
	}
	return alpha;
}

int AIShell::findMinimum(int maxValue, int minValue, int dp, int** gameState) {
	if (dp == 0) {
		return evalFunc(retrieveNumCols(), retrieveNumRows(), retrieveK(), gameState, false);
	}

	int beta = std::numeric_limits<int>::max();
	std::vector<Move> validMoves = checkValidMoves(gameState, true);
	for (int i = 0; i < validMoves.size(); i++) {
		int alpha = findMaximum(maxValue, minValue, dp-1, validMoves[i].gameState);
		beta = std::min(beta, alpha);

		if (beta <= maxValue) {
			return beta;
		}
		minValue = std::min(minValue, beta);
	}
	return beta;
}

int AIShell::retrieveNumCols() {
	return numCols;
}

int AIShell::retrieveNumRows() {
	return numRows;
}

int AIShell::retrieveK() {
	return k;
}
	
//Validation
std::vector<Move> AIShell::checkValidMoves(int** gameState, bool isInOrder) {
	std::vector<Move> validMoves;
	if (gravityOn) {
		for(int col=0; col < numCols; col++) {
			for(int row=numRows-1; row >= 0; row--) {
				if(gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.col = col;
					tempMove.row = row;
					MoveInfo tempMoveInfo = buildValidTree(gameState, !isInOrder, tempMove);
					tempMove.gameState = tempMoveInfo.gameState;
					tempMove.evalValue = evalFunc(retrieveNumCols(), retrieveNumRows(), retrieveK(), tempMoveInfo.gameState, isInOrder);
					validMoves.push_back(tempMove);
					break;
				}
			}
		}
	}
	else {
		for (int col=0; col < numCols; col++) {
			for (int row = 0; row < numRows; row++) {
				if (gameState[col][row] == NO_PIECE) {
					Move tempMove;
					tempMove.col = col;
					tempMove.row = row;
					MoveInfo tempMoveInfo = buildValidTree(gameState, !isInOrder, tempMove);
					tempMove.storedMove = tempMoveInfo;
					tempMove.gameState = tempMoveInfo.gameState;
					tempMove.evalValue = evalFunc(retrieveNumCols(), retrieveNumRows(), retrieveK(), tempMoveInfo.gameState, isInOrder);
					validMoves.push_back(tempMove);
				}
			}
		}
	}

	if (isInOrder) {
		std::stable_sort(validMoves.begin(), validMoves.end());
	}
	else {
		std::stable_sort(validMoves.begin(), validMoves.end(), std::greater<Move>());	
	}

	return validMoves;
}

MoveInfo AIShell::buildValidTree(int** gameState, bool isPlayerTurn, Move tempMove) {
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
}
	
//Alpha Beta
Move AIShell::alphaBetaPruning(int maxValue, int minValue, int dp, MoveInfo storedMove) {
	Move efficientMove;
	int efficientValue = std::numeric_limits<int>::min();
	std::vector<Move> validMoves = checkValidMoves(storedMove.gameState, false);
	for (int i=0; i < validMoves.size(); i++) {
		int valueMax = findMaximum(maxValue, minValue, dp, validMoves[i].gameState);
		if (valueMax >= efficientValue) {
			efficientValue = valueMax;
			efficientMove.col = validMoves[i].col;
			efficientMove.row = validMoves[i].row;
		}
		
	}

	return efficientMove;
}
	
//IDS
Move AIShell::IDS(int maxValue, int minValue, bool isPlayerTurn, MoveInfo storedMove, std::clock_t ct) {
	int dp = 2;
	Move efficientMove;
	for(;(std::clock() - ct)/double(CLOCKS_PER_SEC) * 1000 < deadline; ct = std::clock())
	{
		alphaBetaPruning(maxValue, minValue, dp, storedMove);
		dp++; 
	}

	return retrieveEfficientMove();
}

Move AIShell::retrieveEfficientMove() {
	return efficientMove;
}
