#pragma once

#include "GameStructures.h"

class TetraminoDetail;

class TetraminosFallEventDelegate
{
public:
	TetraminosFallEventDelegate(void);
	virtual ~TetraminosFallEventDelegate(void);

	virtual void placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition) = 0;

};

