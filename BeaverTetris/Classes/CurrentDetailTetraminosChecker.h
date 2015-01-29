#pragma once

#include "GameStructures.h"

class TetraminoDetail;
class CurrentDetailDataSource;

class CurrentDetailTetraminosChecker
{
public:
	CurrentDetailTetraminosChecker();
	~CurrentDetailTetraminosChecker(void);

	bool checkPositionInCurrentDetail(GamePositionOnBoard aPosition);

private:

	CurrentDetailDataSource *_currentDetailDataSource;

	bool positionBelongsToCurrentDetail(GamePositionOnBoard aPosition);
	bool inWidthInterval(GamePositionOnBoard aPosition);
	bool inHeightInterval(GamePositionOnBoard aPosition);
	bool availableTetraminoOnPositionInCurrentDetail(GamePositionOnBoard aPosition);

	TetraminoDetail* getCurrentDetail(); 

};

