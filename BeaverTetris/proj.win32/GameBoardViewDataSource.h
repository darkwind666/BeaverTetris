#pragma once

#include <string>
#include "GameBoard.h"
#include "cocos2d.h"
#include "KeysForEnumsDataSource.h"

class GameBoardViewDataSource
{
public:

	GameBoardViewDataSource(GameBoard *aGameBoard, KeysForEnumsDataSource *aKeysForEnumsDataSource);
	~GameBoardViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);

private:

	GameBoard *_gameBoard;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	int getColumnForIndex(int aIndex);
	int getRowForIndex(int aIndex);

};

