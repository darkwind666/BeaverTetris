#pragma once

#include <vector>
#include "GameStructures.h"
#include "cocos2d.h"

class GameBoard
{
public:
	GameBoard(int width, int height);
	~GameBoard(void);

	void setTetraminoXYposition(Tetramino aTetramino, int xPosition, int yPosition);

	int getGameBoardWidth();
	int getGameBoardHeight();
	Tetramino getTetraminoForXYposition(int xPosition, int yPosition);
	std::vector <cocos2d::Vec2> getAvailableTetraminis();


	void removeTetraminoForXYposition(int xPosition, int yPosition);
	void cleanTetraminoRowForYposition(int yPosition);
	void cleanGameBoard(void);


};

