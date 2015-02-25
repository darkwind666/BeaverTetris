#pragma once

#include "GameSystemInterface.h"

class CurrentDetailDataSource;
class GameTimeStepController;
class TetraminosFallEvent;

class GameFlowSystem: public GameSystemInterface
{
public:
	GameFlowSystem();
	~GameFlowSystem(void);

	void updateSystem(float deltaTime);

private: 

	CurrentDetailDataSource *_currentDetailDataSource;
	GameTimeStepController *_gameTimeStepController;
	TetraminosFallEvent *_tetraminosFallEvent;

	void updateGameFlow();

};

