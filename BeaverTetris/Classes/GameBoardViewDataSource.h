#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameBoard;
class DetailViewDataSource;
class KeysForEnumsDataSource;
class CurrentDetailTetraminosChecker;

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
	DetailViewDataSource *_currentDetailViewDataSource;
	CurrentDetailTetraminosChecker *_currentDetailTetraminosChecker;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	DetailViewDataSource* getDetailViewDataSource();
	TetraminoType getVisibleTetraminoTypeOnPosition(GamePositionOnBoard aPosition);

};

