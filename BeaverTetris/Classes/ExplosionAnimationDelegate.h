#pragma once

#include <vector>
#include <functional>
#include "GameStructures.h"

class ExplosionAnimationDelegate
{
public:
	ExplosionAnimationDelegate(void);
	virtual ~ExplosionAnimationDelegate(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions) = 0;
	virtual void blowUpLine(int aLineIndex) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;
	virtual void setCallback(std::function<void()> aCallback) = 0;

};

