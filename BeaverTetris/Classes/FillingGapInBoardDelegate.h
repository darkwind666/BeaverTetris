#pragma once

#include "GameStructures.h"

class TetraminoDetail;

class FillingGapInBoardDelegate
{
public:
	FillingGapInBoardDelegate(void);
	~FillingGapInBoardDelegate(void);

	virtual void replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition) = 0;

};

