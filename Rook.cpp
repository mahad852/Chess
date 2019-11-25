#include "Rook.h"

Rook::Rook(int block, int c, const char * bmp) : Piece(block, c, bmp)
{
}

bool Rook::RecalculateMS()
{
	return false;
}

