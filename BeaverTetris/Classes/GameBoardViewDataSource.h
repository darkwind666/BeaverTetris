#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameBoard;
class DetailViewDataSource;
class CurrentDetailTetraminosChecker;

class TetraminosInGameBoardViewDataSource;

class GameBoardViewDataSource
{
public:

	GameBoardViewDataSource();
	~GameBoardViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	std::string getTetraminoLivesCountForIndex(int aIndex);
	bool availableTetraminoOnIndex(int aIndex);
	bool availableLevesCountOnIndex(int aIndex);

private:

	GameBoard *_gameBoard;
	DetailViewDataSource *_currentDetailViewDataSource;
	CurrentDetailTetraminosChecker *_currentDetailTetraminosChecker;
	TetraminosInGameBoardViewDataSource *_tetraminosInGameBoardViewDataSource;

	DetailViewDataSource* getDetailViewDataSource();

};

