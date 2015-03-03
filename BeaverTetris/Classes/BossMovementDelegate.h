#pragma once

#include "GameStructures.h"

class BossMovementDelegate
{
public:
	BossMovementDelegate(void);
	virtual ~BossMovementDelegate(void);

	virtual void moveBossFromStartPositionToFinal(GamePositionOnBoard aStartPosition, GamePositionOnBoard aFinalPosition) = 0;

};

