#include "GameManager.h"
#include "conio.h"
#include <iostream>

Piece* GameManager::tracker[64];
Piece* GameManager::pieces_black[16];
Piece* GameManager::pieces_white[16];
Piece* GameManager::graveyard_white[16];
Piece* GameManager::graveyard_black[16];
int GameManager::result;
int GameManager::turn;
bool GameManager::check;
bool GameManager::selected;
bool GameManager::quit;
bool GameManager::checkmate;
int GameManager::selected_block;

void GameManager::RefreshScreen()
{
	//Draw the board first
	Renderer::DrawBoard();

	//Draw Pieces
	for (int i = 0; i < 16; i++)
	{
		// Draw(pixels_piece, x_position, y_position)
		if(pieces_black[i]->GetAcive())
			Renderer::Draw(pieces_black[i]->GetPixels(), pieces_black[i]->GetScreenPos().x, pieces_black[i]->GetScreenPos().y);
	
		if (pieces_white[i]->GetAcive())
			Renderer::Draw(pieces_white[i]->GetPixels(), pieces_white[i]->GetScreenPos().x, pieces_white[i]->GetScreenPos().y);
	}
}

void ClearInputStream()
{
	//Remove all characters from the std in stream
	while (_getch()) {}
}

void GameManager::Init()
{
	turn = WHITE;
	check = false;
	checkmate = false;
	selected = false;
	quit = false;
	Renderer::SetSelect_Active(false);

	//Initialize black pieces
	pieces_black[0] = new King(3, BLACK, BMP_BK);
	pieces_black[1] = new Queen(4, BLACK, BMP_BQ);
	pieces_black[2] = new Bishop(2, BLACK, BMP_BB);
	pieces_black[3] = new Bishop(5, BLACK, BMP_BB);
	pieces_black[4] = new Knight(1, BLACK, BMP_BH);
	pieces_black[5] = new Knight(6, BLACK, BMP_BH);
	pieces_black[6] = new Rook(0, BLACK, BMP_BR);
	pieces_black[7] = new Rook(7, BLACK, BMP_BR);
	pieces_black[8] = new Pawn(8, BLACK, BMP_BP);
	pieces_black[9] = new Pawn(9, BLACK, BMP_BP);
	pieces_black[10] = new Pawn(10, BLACK, BMP_BP);
	pieces_black[11] = new Pawn(11, BLACK, BMP_BP);
	pieces_black[12] = new Pawn(12, BLACK, BMP_BP);
	pieces_black[13] = new Pawn(13, BLACK, BMP_BP);
	pieces_black[14] = new Pawn(14, BLACK, BMP_BP);
	pieces_black[15] = new Pawn(15, BLACK, BMP_BP);

	//Initialize white pieces
	pieces_white[0] = new King(59, WHITE, BMP_WK);
	pieces_white[1] = new Queen(60, WHITE, BMP_WQ);
	pieces_white[2] = new Bishop(58, WHITE, BMP_WB);
	pieces_white[3] = new Bishop(61, WHITE, BMP_WB);
	pieces_white[4] = new Knight(57, WHITE, BMP_WH);
	pieces_white[5] = new Knight(62, WHITE, BMP_WH);
	pieces_white[6] = new Rook(56, WHITE, BMP_WR);
	pieces_white[7] = new Rook(63, WHITE, BMP_WR);
	pieces_white[8] = new Pawn(48, WHITE, BMP_WP);
	pieces_white[9] = new Pawn(49, WHITE, BMP_WP);
	pieces_white[10] = new Pawn(50, WHITE, BMP_WP);
	pieces_white[11] = new Pawn(51, WHITE, BMP_WP);
	pieces_white[12] = new Pawn(52, WHITE, BMP_WP);
	pieces_white[13] = new Pawn(53, WHITE, BMP_WP);
	pieces_white[14] = new Pawn(54, WHITE, BMP_WP);
	pieces_white[15] = new Pawn(55, WHITE, BMP_WP);
	
	//Update tracker with initial positions
	UpdateTracker();

	//Init movesets
	for (int i = 0; i < 16; i++)
	{
		pieces_white[i]->RecalculateMS();
		pieces_black[i]->RecalculateMS();
	}

	//Initialize marker
	Renderer::SetMarker(32);
}

void GameManager::EndGame()
{
	for (int i = 0; i < 16; i++)
	{
		delete pieces_white[i];
		delete pieces_black[i];
	}
}

void GameManager::AttemptMove()
{
	std::cout << "Attempting to move " << std::endl;
	int move_block = Renderer::GetMarker();
	Piece* move_piece = tracker[selected_block];
	bool legal = true;

	if (!move_piece->CanMove(move_block))
		return;

	std::cout << "Can move " << std::endl;

	Piece* temp = tracker[move_block];
	tracker[move_block] = move_piece;
	tracker[selected_block] = 0;

	Piece** opponent = turn ? pieces_black : pieces_white;

	std::cout << "Checking Legal " << std::endl;
	legal = IsLegal(opponent);

	if (!legal)
	{
		std::cout << "ILLEGAL " << std::endl;
		tracker[selected_block] = move_piece;
		tracker[move_block] = temp;
		IsLegal(opponent);
		return;
	}

	//Kill code... Checks if move block is empty, kills piece if not empty
	if (temp != 0)
	{
		temp->SetAcive(false);
	}

	std::cout << "Moving piece " << std::endl;
	move_piece->Move(move_block);
	UpdateTracker();
	DeselectBlock();
	Renderer::ReDrawBlocks(move_block, selected_block, move_piece->GetPixels(), 0);
	turn = !turn;
}

bool GameManager::IsLegal(Piece ** opponent_pieces)
{
	for (int i = 0; i < 16; i++)
	{
		std::cout << "For piece " << i << std::endl;
		if (!opponent_pieces[i]->GetAcive())
			continue;

		else if (opponent_pieces[i]->RecalculateMS())
			return false;

	}
	return true;
}

Piece ** GameManager::GetTracker()
{
	return tracker;
}

void GameManager::HandleInput()
{
	//Take char input
	char input = _getch();


	switch (input)
	{

	//Update marker position accordingly
	case 'w':
	case 'a':
	case 's':
	case 'd':
		Renderer::UpdateMarker(input);
		break;

	//Refresh screen
	case 'r':
		RefreshScreen();
		break;

	//Quit game
	case 'q':
		quit = true;
		result = QUIT;
		break;

	//Select block
	case ' ':
		if (selected)
		{
			AttemptMove();
			break;
		}

		selected_block = Renderer::GetMarker();
		std::cout << "Selected " << selected_block << std::endl;
		
		std::cout << "Tracker at block " << tracker[selected_block] << std::endl;
		if(!tracker[selected_block])
			break;
		

		std::cout << "Checking color " << std::endl;
		if (tracker[selected_block]->GetColor() != turn)
			break;

		SelectBlock();
		break;

	case 'e':
		DeselectBlock();
		return;
	}

}

void GameManager::SelectBlock()
{
	Renderer::MarkBlock(Renderer::GetMarker(), SELECTED_MARKER_COLOR);
	Renderer::SetSelected(selected_block);
	Renderer::SetSelect_Active(true);
	selected = true;
}

void GameManager::DeselectBlock()
{
	Renderer::EraseMarker(selected_block);
	Renderer::SetSelected(-1);
	Renderer::SetSelect_Active(false);
	selected = false;
}

void GameManager::StartMatch()
{
	system("pause");
	system("cls");
	RefreshScreen();

	while (!checkmate && !quit)
	{
		//Check for input without waiting for enter
		if (_kbhit() != 0)
		{
			HandleInput();
			ClearInputStream();
		}
	}		
}

void GameManager::UpdateTracker()
{
	//Clear the tracker
	for (int i = 0; i < 64; i++)
		tracker[i] = 0;

	for (int i = 0; i < 16; i++)
	{
		//Update the tracker by assigning piece at appropriate index
		if(pieces_white[i]->GetAcive())
			tracker[pieces_white[i]->GetBlock()] = pieces_white[i];
		if(pieces_black[i]->GetAcive())
			tracker[pieces_black[i]->GetBlock()] = pieces_black[i];
	}

}

void GameManager::DisplayResult()
{
	if (quit)
		std::cout << "You quit the game" << std::endl;
	else if (checkmate)
	{
		if (result == WHITE_WIN)
			std::cout << "White wins!!!!!!" << std::endl;
		else if (result == BLACK_WIN)
			std::cout << "Black wins!!!!!!" << std::endl;
	}
}