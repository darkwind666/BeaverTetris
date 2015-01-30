#pragma once

#include "GameStructures.h"
#include "cocos2d.h"
#include <string>

class CurrentDetailDataSource;
class KeysForEnumsDataSource;
class TetraminoDetail;
class Tetramino;

class CurrentDetailViewDataSource
{
public:
	CurrentDetailViewDataSource(void);
	~CurrentDetailViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	bool availableTetraminoOnIndex(int aIndex);

	cocos2d::Vec2 getTetraminosViewOffset();

	TetraminoType getTetraminoTypeOnPositionInCurrentDetail(GamePositionOnBoard aPosition);

private:

	CurrentDetailDataSource *_currentDetailDataSource;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	Tetramino* getTetraminoOnIndex(int aIndex);
	TetraminoDetail* getCurrentDetail(); 

};

