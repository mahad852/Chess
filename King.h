#pragma once
#include "Piece.h"

class King : public Piece
{
private:
	bool inCheck = false;
public:
	King(int block, int c, const char* bmp);
	bool RecalculateMS();
};
