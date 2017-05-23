#include "Move.h"


Move::Move()
{
	row = 0;
	col = 0;
	evalValue = 0;
}

Move::Move(int col, int row){
	this->row=row;
	this->col=col;
}

bool operator<(const Move& lhs, const Move& rhs) {
	if (lhs.evalValue < rhs.evalValue) {
		return true;
	}
	return false;
}

bool operator>(const Move& lhs, const Move& rhs) {
	if (lhs.evalValue > rhs.evalValue) {
		return true;
	}
	return false;
}