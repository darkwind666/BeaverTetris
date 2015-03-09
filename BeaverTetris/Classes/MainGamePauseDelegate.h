#pragma once

#include "ServiceInterface.h"

class MainGamePauseEndObserver;

class MainGamePauseDelegate : public ServiceInterface
{
public:
	MainGamePauseDelegate(void);
	~MainGamePauseDelegate(void);

	void endPause();
	void addObserver(MainGamePauseEndObserver *aObserver);

private:

	MainGamePauseEndObserver *_observer;

};

