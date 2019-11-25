#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(int block, int c, const char* bmp);
	bool RecalculateMS();
};
