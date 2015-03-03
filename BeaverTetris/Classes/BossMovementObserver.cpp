#include "BossMovementObserver.h"
#include "BossMovementDelegate.h"

BossMovementObserver::BossMovementObserver(void)
{
	_delegate = NULL;
}


BossMovementObserver::~BossMovementObserver(void)
{
}

void BossMovementObserver::moveBossFromStartPositionToFinal(GamePositionOnBoard aStartPosition, GamePositionOnBoard aFinalPosition)
{
	if (_delegate)
	{
		_delegate->moveBossFromStartPositionToFinal(aStartPosition, aFinalPosition);
	}
}

void BossMovementObserver::setDelegate(BossMovementDelegate *aDelegate)
{
	_delegate = aDelegate;
}