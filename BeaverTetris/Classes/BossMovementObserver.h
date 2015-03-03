#pragma once

#include "ServiceInterface.h"
#include "GameStructures.h"

class BossMovementDelegate;

class BossMovementObserver : public ServiceInterface
{
public:
	BossMovementObserver(void);
	~BossMovementObserver(void);

	void moveBossFromStartPositionToFinal(GamePositionOnBoard aStartPosition, GamePositionOnBoard aFinalPosition);
	void setDelegate(BossMovementDelegate *aDelegate);

private:

	BossMovementDelegate *_delegate;

};

