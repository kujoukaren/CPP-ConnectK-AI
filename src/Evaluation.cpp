#include "Evaluation.h"


Evaluation::Evaluation() {
	/*numRows = 0;
	numCols = 0;
	k = 0;
	counterMax = 0;
	counterMin = 0;
	valueMax = 0;
	valueMin = 0;
	isFirstPlayer = false;
	gravityOn = false;
	isBlocked = false;*/
}

/*Evaluation::Evaluation(int numRows, int numCols, int k, int **gameState, bool isFirstPlayer, bool gravityOn) {
	this->numRows = numRows;
	this->numCols = numCols;
	this->k = k;
	counterMax = 0;
	counterMin = 0;
	valueMax = 0;
	valueMin = 0;
	this->gameState = gameState;
	this->isFirstPlayer = isFirstPlayer;
	this->gravityOn = gravityOn;
	isBlocked = false;
}*/

int Evaluation::evalFunc(int numCols, int numRows, int k, int** gameState, bool gravityOn, bool isFirstPlayer) {
	double valueMax = 0;
	double valueMin = 0;
	
	int** listMax = new int*[4];
	int** listMin = new int*[4];
	for(int index=0; index < 4; index++) {
		listMax[index] = new int[k+1];
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
			valueMax += (double)row * listMax[col][row] * pow(5,row);
			valueMin -= (double)row * listMin[col][row] * pow(5,row);
		}
	}

	for(int col=0; col < 4; col++)	{
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
		int valueTotal = 0;
		for (int col=0; col < numCols; col++) {
			for (int row=0; row < numRows; row++) {
				GameStateChecker gsc;
				valueTotal += gsc.findAll(col, numCols, row, numRows, k, gameState, true);
			}
		}
		return valueTotal;
	}
	else
	{
		if(isFirstPlayer)
		{
			//return -(valueMax-valueMin);
			return valueMin-valueMax;

		}
		else
		{
			//return -(valueMin+valueMax);
			return -valueMin-valueMax;
		}
	}

	/*initList();
	boardCheck();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < k + 1; j++) {
			valueMax = valueMax + ((double)j*listMax[i][j]*std::pow(5,j));
			valueMin = valueMin - ((double)j*listMin[i][j]*std::pow(5,j));
		}
	}
	
	for (int t = 0; t < 4; t++) {
		for (int i = 0; i < 4; i++) {
			switch(t){
				case 0:
					if (listMin[i][k-1] != 0) {
						valueMin = std::numeric_limits<int>::min() + 3;
					}
					break;
				case 1:
					if (listMin[i][k-2] != 0) {
						valueMin = std::numeric_limits<int>::min() + 2;
					}
					break;
				case 2:
					if (listMin[i][k] != 0) {
						valueMin = std::numeric_limits<int>::min() + 1;
					}
					break;
				case 3:
					if (listMax[i][k] != 0) {
						valueMax = std::numeric_limits<int>::max() - 1;
					}
					break;
			}	
		}
		
		deleList();
		
		if(gravityOn) {
			int valueTotal = 0;
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					GameStateChecker gsc(col, numCols, row, numRows, k, gameState, isFirstPlayer);
					valueTotal = valueTotal + gsc.findAll();
				}
			}
			return valueTotal;
		}
		else {
			if(isFirstPlayer) {
				return -valueMax+valueMin;
			}
			else {
				return -valueMax-valueMin;
			}
		}
	}*/
}

void Evaluation::boardCheck(int numCols, int numRows, int k, int** listMax, int** listMin, int** gameState) {
	int counterMax = 0;
	int counterMin = 0;
	bool isBlocked = false;
	for (int col=0; col < numCols-k; col++) {
		for (int row=0; row <= numRows; row++) {
			for (int i=0; i < k; i++) {
				if (gameState[col+i][row] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col+i][row] == HUMAN_PIECE) {
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
			for (int i=0; i < k; i++) {
				if (gameState[col][row+i] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col][row+i] == HUMAN_PIECE) {
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
			for (int i = 0; i < k; i++) {
				if (gameState[col+i][row+i] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col+i][row+i] == HUMAN_PIECE) {
					counterMin += 1;
				}
			}
			if (counterMax > 0 && counterMin > 0) {
				isBlocked = true;
			}
			if (!isBlocked){
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
			for (int i=0; i < k; i++) {
				if (gameState[col-i][row+i] == AI_PIECE) {
					counterMax += 1;
				}
				else if (gameState[col-i][row+i] == HUMAN_PIECE) {
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

	/*counterMax = 0;
	counterMin = 0;
	isBlocked = false;
	
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c <= numCols - k; c++) {
			for (int n = 0; n < k; n++) {
				if (gameState[c+n][r] == HUMAN_PIECE) {
					counterMin += 1;
				}
				else if (gameState[c+n][r] == AI_PIECE) {
					counterMax += 1;
				}
		
				if (counterMax > 0 && counterMin > 0) {
					isBlocked = true;
				}
				
				if (isBlocked == false) {
					listMax[0][counterMax] += 1;
					listMin[0][counterMin] += 1;
				}
				counterMax = 0;
				counterMin = 0;
				isBlocked = false;
			}
			
		}
	}
	
	for (int r = 0; r < numRows - k; r++) {
		for (int c = 0; c <= numCols; c++) {
			for (int n = 0; n < k; n++) {
				if (gameState[c][r+n] == HUMAN_PIECE) {
					counterMin += 1;
				}
				else if (gameState[c][r+n] == AI_PIECE) {
					counterMax += 1;
				}
		
				if (counterMax > 0 && counterMin > 0) {
					isBlocked = true;
				}
				
				if (isBlocked == false) {
					listMax[1][counterMax] += 1;
					listMin[1][counterMin] += 1;
				}
				counterMax = 0;
				counterMin = 0;
				isBlocked = false;
			}
			
		}
	}
	
	for (int r = 0; r < numRows - k; r++) {
		for (int c = 0; c <= numCols - k; c++) {
			for (int n = 0; n < k; n++) {
				if (gameState[c+n][r+n] == HUMAN_PIECE) {
					counterMin += 1;
				}
				else if (gameState[c+n][r+n] == AI_PIECE) {
					counterMax += 1;
				}
		
				if (counterMax > 0 && counterMin > 0) {
					isBlocked = true;
				}
				
				if (isBlocked == false) {
					listMax[2][counterMax] += 1;
					listMin[2][counterMin] += 1;
				}
				counterMax = 0;
				counterMin = 0;
				isBlocked = false;
			}
			
		}
	}
	
	for (int r = numRows - k; r >= 0; r--) {
		for (int c = numCols - 1; c >= k - 1; c--) {
			for (int n=0; n<k; n++) {
				if (gameState[c-k][r+k] == HUMAN_PIECE) {
					counterMin += 1;
				}
				else if (gameState[c-k][r+k] == AI_PIECE) {
					counterMax += 1;
				}
		
				if (counterMax > 0 && counterMin > 0) {
					isBlocked = true;
				}
				
				if (isBlocked == false) {
					listMax[3][counterMax] += 1;
					listMin[3][counterMin] += 1;
				}
				counterMax = 0;
				counterMin = 0;
				isBlocked = false;
			}
			
		}
	}*/
}

/*void Evaluation::initList() {
	listMax = new int*[4];
	listMin = new int*[4];
	for (int i = 0; i < 4; i++) {
		listMax[i] = new int[k+1];
		listMin[i] = new int[k+1];
	}

	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < k + 1; row ++) {
			listMax[col][row] = 0;
			listMin[col][row] = 0;
		}
	}
}

void Evaluation::deleList() {
	for (int d = 0; d < 4; d++) {
		delete[] listMax[d];
		delete[] listMin[d];
	}
	delete[] listMax;
	delete[] listMin;
}*/