#ifndef MOVE_H
#define MOVE_H

#pragma once


struct MoveInfo {
	int row;
	int col;
	int evalValue;
	int **gameState;
};

class Move
{
public:
	MoveInfo storedMove;

	int row; //the row to move to. 
	int col; //the col to move to.
	int evalValue;
	int **gameState;

	Move();
	Move(int col, int row);
};

bool operator<(const Move& lhs, const Move& rhs);
bool operator>(const Move& lhs, const Move& rhs);

#endif //MOVE_H
