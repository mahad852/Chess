#pragma once
#include "Piece.h"
class Pawn : public Piece
{
private:
	bool firstTurn = true;
public:
	Pawn(int block, int c, const char* bmp);
	bool RecalculateMS();
};
