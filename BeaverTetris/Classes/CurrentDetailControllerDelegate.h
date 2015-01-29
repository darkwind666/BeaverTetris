#pragma once

#include "GameStructures.h"

class CurrentDetailControllerDelegate
{
public:
	CurrentDetailControllerDelegate(void);
	virtual ~CurrentDetailControllerDelegate(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition) = 0;

};

