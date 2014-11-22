#pragma once

#include <string>
#include "GameBoard.h"
#include "cocos2d.h"

class GameBoardViewDataSource
{
public:

	GameBoardViewDataSource(GameBoard *aGameBoard);
	~GameBoardViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);

private:

	GameBoard *_gameBoard;


};

