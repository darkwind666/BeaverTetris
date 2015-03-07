#pragma once

#include "GameSystemInterface.h"

class CurrentDetailDataSource;
class GameTimeStepController;
class TetraminosFallEvent;
class TimeAccelerationEvent;

class GameFlowSystem: public GameSystemInterface
{
public:
	GameFlowSystem(GameTimeStepController *aGameTimeStepController);
	~GameFlowSystem(void);

	void updateSystem(float deltaTime);

private: 

	CurrentDetailDataSource *_currentDetailDataSource;
	GameTimeStepController *_gameTimeStepController;
	TetraminosFallEvent *_tetraminosFallEvent;
	TimeAccelerationEvent *_timeAccelerationEvent;

	void updateGameFlow();
	void runAvailableEvent();
	void makeNewDetail();

};

