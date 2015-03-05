#pragma once

#include "GameStructures.h"
#include "FuctionsTypedefs.h"
#include "cocos2d.h"
#include <string>

class KeysForEnumsDataSource;
class TetraminoDetail;
class Tetramino;

class DetailViewDataSource
{
public:
	DetailViewDataSource(std::function<TetraminoDetail*()> aDetailDataSource);
	~DetailViewDataSource(void);

	int getTetraminosCount();
	std::string getTetraminoImageForIndex(int aIndex);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	bool availableTetraminoOnIndex(int aIndex);

	cocos2d::Vec2 getTetraminosViewOffset();
	cocos2d::Vec2 getDetailPositionOnView();
	cocos2d::Vec2 getPositionOnView(GamePositionOnBoard aPosition);
	std::string getTetraminoImageForAbsolutePosition(GamePositionOnBoard aPosition);
	GamePositionOnBoard getTetraminoPositionInBoardForIndex(int aIndex);
	GamePositionOnBoard getDetailPositionOnBoard();

	void cleanDetailWithCleanerCallback(DetailCleaner aCleanerCallback);

private:

	std::function<TetraminoDetail*()> _detailDataSource;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	Tetramino* getTetraminoOnIndex(int aIndex);
	void cleanTetraminoWithCleanerForXY(DetailCleaner aCleanerCallback, int xPosition, int yPosition);
	TetraminoDetail* getCurrentDetail(); 

};

