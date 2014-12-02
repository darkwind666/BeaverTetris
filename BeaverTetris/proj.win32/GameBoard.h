#pragma once

#include <vector>
#include "GameStructures.h"
#include "Tetramino.h"

class GameBoard
{
public:
	GameBoard(int width, int height);
	~GameBoard(void);

	void setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition);

	int getGameBoardWidth();
	int getGameBoardHeight();
	Tetramino* getTetraminoForXYposition(int xPosition, int yPosition);
	std::vector <GamePositionOnBoard> getAvailableTetraminis();

	void removeTetraminoForXYposition(int xPosition, int yPosition);
	void removeTetraminos(std::vector <GamePositionOnBoard> aNeedToRemoveTetraminos);
	void cleanTetraminoRowForYposition(int yPosition);
	void cleanGameBoard(void);

private:

	Tetramino **_tetramins;
	int _gameBoardWidth;
	int _gameBoardHeight;

};

