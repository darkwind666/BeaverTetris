#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameBoard;
class KeysForEnumsDataSource;

class TetraminosInGameBoardViewDataSource
{
public:
	TetraminosInGameBoardViewDataSource(void);
	~TetraminosInGameBoardViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	std::string getTetraminoLivesCountForIndex(int aIndex);
	bool availableTetraminoOnIndex(int aIndex);
	bool availableLevesCountOnIndex(int aIndex);

private:

	GameBoard *_gameBoard;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

};

