#include "GameStateChecker.h"


GameStateChecker::GameStateChecker() {
	/*row = 0;
	col = 0;
	numRows = 0;
	numCols = 0;
	k = 0;
	isFirstPlayer = false;*/
}

/*GameStateChecker::GameStateChecker(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	this->row = row;
	this->col = col;
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	this->gameState = gameState;
	this->isFirstPlayer = isFirstPlayer;
}*/

int GameStateChecker::findAll(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	int n = north(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int w = west(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int e = east(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int s = south(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int nw = northWest(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int ne = northEast(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int sw = southWest(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int se = southEast(col, numCols, row, numRows, k, gameState, isFirstPlayer);
	int evalValue = n + w + e + s + nw + ne + sw + se;
	return evalValue;
}

int GameStateChecker::north(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row-k+1 < 0) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col][row-i] != PLAYER && gameState[col][row-i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col][row-i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int northValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if ((row - k + 1) >= 0) {
			for (int n = 0; n < k; n++) {
				int pos = gameState[col][row - n];
				if (pos == PLAYER) {
					northValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (northValue == k) {
				northValue = 10000;
			}
			else if (PLAYER == 1) {
				if (northValue == k-1) {
					if (isFirstPlayer) {
						northValue = 300;
					}
					else {
						northValue = 3000;
					}
				}
				else if (northValue == k-2) {
					northValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (northValue == k-1) {
					if (isFirstPlayer) {
						northValue = 3000;
					}
					else {
						northValue = 300;
					}
				}
				else if (northValue == k-2) {
					northValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return northValue;
			}
			else {
				return -northValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::west(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int westValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col-i][row] != PLAYER && gameState[col-i][row] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-i][row] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int westValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if ((col - k + 1) >= 0) {
			for (int w = 0; w < k; w++) {
				int pos = gameState[col - w][row];
				if (pos == PLAYER) {
					westValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (westValue == k) {
				westValue = 10000;
			}
			else if (PLAYER == 1) {
				if (westValue == k-1) {
					if (isFirstPlayer) {
						westValue = 300;
					}
					else {
						westValue = 3000;
					}
				}
				else if (westValue == k-2) {
					westValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (westValue == k-1) {
					if (isFirstPlayer) {
						westValue = 3000;
					}
					else {
						westValue = 300;
					}
				}
				else if (westValue == k-2) {
					westValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return westValue;
			}
			else {
				return -westValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::east(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int eastValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col+k > numCols) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col+i][row] != PLAYER && gameState[col+i][row] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+i][row] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int eastValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if ((col + k) <= numCols) {
			for (int e = 0; e < k; e++) {
				int pos = gameState[col + e][row];
				if (pos == PLAYER) {
					eastValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (eastValue == k) {
				eastValue = 10000;
			}
			else if (PLAYER == 1) {
				if (eastValue == k-1) {
					if (isFirstPlayer) {
						eastValue = 300;
					}
					else {
						eastValue = 1000;
					}
				}
				else if (eastValue == k-2) {
					eastValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (eastValue == k-1) {
					if (isFirstPlayer) {
						eastValue = 1000;
					}
					else {
						eastValue = 300;
					}
				}
				else if (eastValue == k-2) {
					eastValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return eastValue;
			}
			else {
				return -eastValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::south(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row+k > numRows) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col][row+i] != PLAYER && gameState[col][row+i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col][row+i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int southValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if ((row + k) <= numRows) {
			for (int s = 0; s < k; s++) {
				int pos = gameState[col][row + s];
				if (pos == PLAYER) {
					southValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (southValue == k) {
				southValue = 10000;
			}
			else if (PLAYER == 1) {
				if (southValue == k-1) {
					if (isFirstPlayer) {
						southValue = 300;
					}
					else {
						southValue = 3000;
					}
				}
				else if (southValue == k-2) {
					southValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (southValue == k-1) {
					if (isFirstPlayer) {
						southValue = 3000;
					}
					else {
						southValue = 300;
					}
				}
				else if (southValue == k-2) {
					southValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return southValue;
			}
			else {
				return -southValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::northWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northWestValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0 || row-k+1 < 0) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col-i][row-i] != PLAYER && gameState[col-i][row-i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-i][row-i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int northWestValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if (((col - k + 1) >= 0) || (row - k + 1) >= numRows) {
			for (int nw = 0; nw < k; nw++) {
				int pos = gameState[col - nw][row - nw];
				if (pos == PLAYER) {
					northWestValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (northWestValue == k) {
				northWestValue = 10000;
			}
			else if (PLAYER == 1) {
				if (northWestValue == k-1) {
					if (isFirstPlayer) {
						northWestValue = 300;
					}
					else {
						northWestValue = 3000;
					}
				}
				else if (northWestValue == k-2) {
					northWestValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (northWestValue == k-1) {
					if (isFirstPlayer) {
						northWestValue = 3000;
					}
					else {
						northWestValue = 300;
					}
				}
				else if (northWestValue == k-2) {
					northWestValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return northWestValue;
			}
			else {
				return -northWestValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::northEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int northEastValue = 0;
	if (PLAYER != NO_PIECE) {
		if (row-k+1 < 0 || col+k > numCols) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col+i][row-i] != PLAYER && gameState[col+i][row-i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+i][row-i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int northEastValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if (((col + k) <= numCols) || ((row - k + 1) >= 0)) {
			for (int ne = 0; ne < k; ne++) {
				int pos = gameState[col + ne][row - ne];
				if (pos == PLAYER) {
					northEastValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (northEastValue == k) {
				northEastValue = 10000;
			}
			else if (PLAYER == 1) {
				if (northEastValue == k-1) {
					if (isFirstPlayer) {
						northEastValue = 300;
					}
					else {
						northEastValue = 3000;
					}
				}
				else if (northEastValue == k-2) {
					northEastValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (northEastValue == k-1) {
					if (isFirstPlayer) {
						northEastValue = 3000;
					}
					else {
						northEastValue = 300;
					}
				}
				else if (northEastValue == k-2) {
					northEastValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return northEastValue;
			}
			else {
				return -northEastValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::southWest(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southWestValue = 0;
	if (PLAYER != NO_PIECE) {
		if (col-k+1 < 0 || row+k > numRows) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col-i][row+i] != PLAYER && gameState[col-i][row+i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col-i][row-i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int southWestValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if (((col - k + 1) >= 0) || ((row + k) <= numRows)) {
			for (int sw = 0; sw < k; sw++) {
				int pos1 = gameState[col - sw][row - sw];
				int pos2 = gameState[col - sw][row + sw];
				if (pos1 == PLAYER) {
					southWestValue++;
				}
				else if (pos2 != NO_PIECE && pos2 != PLAYER) {
					return 0;
				}
			}
			
			if (southWestValue == k) {
				southWestValue = 10000;
			}
			else if (PLAYER == 1) {
				if (southWestValue == k-1) {
					if (isFirstPlayer) {
						southWestValue = 300;
					}
					else {
						southWestValue = 3000;
					}
				}
				else if (southWestValue == k-2) {
					southWestValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (southWestValue == k-1) {
					if (isFirstPlayer) {
						southWestValue = 3000;
					}
					else {
						southWestValue = 300;
					}
				}
				else if (southWestValue == k-2) {
					southWestValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return southWestValue;
			}
			else {
				return -southWestValue;
			}
		}
	}
	return 0;*/
}

int GameStateChecker::southEast(int col, int numCols, int row, int numRows, int k, int** gameState, bool isFirstPlayer) {
	const int PLAYER = gameState[col][row];
	int southEastValue = 0;
	if (PLAYER != NO_PIECE) {
		if ((col+k > numCols) || (row+k > numRows)) {
			return 0;
		}
		else {
			for (int i=0; i < k; i++) {
				if (gameState[col+i][row+i] != PLAYER && gameState[col+i][row+i] != NO_PIECE) {
					return 0;
				}
				else if (gameState[col+i][row+i] == PLAYER) {
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

	/*const int PLAYER = gameState[col][row];
	int southEastValue = 0;
	if (PLAYER == AI_PIECE || PLAYER == HUMAN_PIECE) {
		if (((col + k) <= numCols) || ((row + k) <= numRows)) {
			for (int se = 0; se < k; se++) {
				int pos = gameState[col + se][row + se];
				if (pos == PLAYER) {
					southEastValue++;
				}
				else if (pos != NO_PIECE && pos != PLAYER) {
					return 0;
				}
			}
			
			if (southEastValue == k) {
				southEastValue = 10000;
			}
			else if (PLAYER == 1) {
				if (southEastValue == k-1) {
					if (isFirstPlayer) {
						southEastValue = 300;
					}
					else {
						southEastValue = 3000;
					}
				}
				else if (southEastValue == k-2) {
					southEastValue = 300;
				}
			}
			else if (PLAYER == -1) {
				if (southEastValue == k-1) {
					if (isFirstPlayer) {
						southEastValue = 3000;
					}
					else {
						southEastValue = 300;
					}
				}
				else if (southEastValue == k-2) {
					southEastValue = 300;
				}
			}
			
			if (PLAYER == AI_PIECE) {
				return southEastValue;
			}
			else {
				return -southEastValue;
			}
		}
	}
	return 0;*/
}















