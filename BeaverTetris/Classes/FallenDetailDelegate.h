#pragma once

#include "GameStructures.h"

class TetraminoDetail;

class FallenDetailDelegate
{
public:
	FallenDetailDelegate(void);
	virtual ~FallenDetailDelegate(void);

	virtual void placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition) = 0;
	virtual void replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition) = 0;

};

