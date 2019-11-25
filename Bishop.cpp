#include "Bishop.h"

Bishop::Bishop(int block, int c, const char * bmp) : Piece(block, c, bmp)
{
	type = BISHOP;
}

bool Bishop::RecalculateMS()
{
	return false;
}