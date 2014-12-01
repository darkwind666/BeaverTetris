#pragma once

#include "CurrentDetailController.h"

class GameFlowController
{
public:
	GameFlowController(CurrentDetailController *aCurrentDetailController);
	~GameFlowController(void);

	void makeNewGameEvent();

private: 

	CurrentDetailController *_currentDetailController;

};

