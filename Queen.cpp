#include "Queen.h"
#include "GameManager.h"

Queen::Queen(int block, int c, const char * bmp) : Piece(block, c, bmp)
{
	type = QUEEN;
}

bool Queen::RecalculateMS()
{
	int x = board_pos.x;
	int y = board_pos.y;
	
	int id;
	
	int counter = 0;

	bool kingCheck = false;

	for (int i = 0; i < 64; i++)
		moveset[i] = -1;

	//For vertical up
	for (int i = 1;; i++)
	{	
		if (y + i > 7)
			break;

		id = Utils::IndexToBlock(x, y + i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}
	
	//for vertical down
	for (int i = 1;; i++)
	{
		if (y - i < 0)
			break;

		id = Utils::IndexToBlock(x, y - i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}
	//for horizontal right
	for (int i = 1;; i++)
	{
		if (x + i > 7)
			break;

		id = Utils::IndexToBlock(x + i, y);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}
	//for horizontal left
	for (int i = 1;; i++)
	{
		if (x - i < 0)
			break;

		id = Utils::IndexToBlock(x - i, y);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}

	//for diagnol Right Up
	for (int i = 1;; i++)
	{
		if (x + i > 7 || y + i > 7)
			break;

		id = Utils::IndexToBlock(x + i, y + i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}

	//for diagnol right down
	for (int i = 1; ; i++)
	{
		if (x - i < 0 || y - i < 0)
			break;
		
		id = Utils::IndexToBlock(x - i, y - i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}

	//for diagnol left up
	for (int i = 1; ; i++)
	{
		if (x - i < 0 || y + i > 7)
			break;

		id = Utils::IndexToBlock(x - i, y + i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id;
		counter++;
	}
	
	//for diagnol left down
	for (int i = 1;; i++)
	{
		if (x + i > 7 || y - i < 0)
			break;

		id = Utils::IndexToBlock(x + i, y - i);

		if (stopMoving(id, counter, kingCheck))
			break;

		moveset[counter] = id; 
		counter++;
	}

	return kingCheck;
}


bool Queen::stopMoving(int id, int &counter, bool &kingCheck)
{
	Piece** board = GameManager::GetTracker();

	if (board[id] != NULL)
	{
		if (board[id]->GetColor() != color)
		{
			if (board[id]->GetType() == KING)
				kingCheck = true;
			moveset[counter] = id;
			counter++;
		}
		return true;
	}

	else
		return false;
}
