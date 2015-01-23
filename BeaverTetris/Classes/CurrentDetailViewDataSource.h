#pragma once

#include "GameStructures.h"

class CurrentDetailDataSource;

class CurrentDetailViewDataSource
{
public:
	CurrentDetailViewDataSource(void);
	~CurrentDetailViewDataSource(void);

	bool checkPositionInCurrentDetail(GamePositionOnBoard aPosition);
	TetraminoType getTetraminoTypeOnPositionInCurrentDetail(GamePositionOnBoard aPosition);

private:

	CurrentDetailDataSource *_currentDetailDataSource;

	bool positionBelongsToCurrentDetail(GamePositionOnBoard aPosition);
	bool inWidthInterval(GamePositionOnBoard aPosition);
	bool inHeightInterval(GamePositionOnBoard aPosition);
	bool availableTetraminoOnPositionInCurrentDetail(GamePositionOnBoard aPosition);
	GamePositionOnBoard convertPositionInCurrentDetailPosition(GamePositionOnBoard aPosition);

};

