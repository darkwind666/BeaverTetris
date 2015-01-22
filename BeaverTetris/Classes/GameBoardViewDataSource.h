#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameBoard;
class KeysForEnumsDataSource;

class GameBoardViewDataSource
{
public:

	GameBoardViewDataSource();
	~GameBoardViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	bool availableTetraminoOnIndex(int aIndex);

private:

	GameBoard *_gameBoard;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	GamePositionOnBoard getPositionForIndex(int aIndex);
	int getColumnForIndex(int aIndex);
	int getRowForIndex(int aIndex);

};

