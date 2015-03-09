#include "MainGamePauseDelegate.h"
#include "MainGamePauseEndObserver.h"
#include <stdlib.h>

MainGamePauseDelegate::MainGamePauseDelegate(void)
{
	_observer = NULL;
}


MainGamePauseDelegate::~MainGamePauseDelegate(void)
{
}

void MainGamePauseDelegate::endPause()
{
	if (_observer)
	{
		_observer->pauseWasEnded();
	}
}

void MainGamePauseDelegate::addObserver(MainGamePauseEndObserver *aObserver)
{
	_observer = aObserver;
}