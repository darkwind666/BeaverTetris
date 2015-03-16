#pragma once

#include "GameSystemInterface.h"
#include <vector>
#include <string>
#include "GameEnums.h"
#include "GameStructures.h"

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

	void makeGameEvents();
	void makeFallDetailsEventWithData(std::vector<GameEventInformation> &availableEvents);
	void makeAccelerationEventWithData(std::vector<GameEventInformation> &availableEvents);
	void makeEventsWithData(std::vector<GameEventInformation> &availableEvents);
	bool findEventForTypeInEvents(GameEventType aType, std::vector<GameEventInformation> &availableEvents);
	int getIndexForTypeInEvents(GameEventType aType, std::vector<GameEventInformation> &availableEvents);

	void updateGameFlow();
	void updateEvents();
	void runAvailableEvent();
	void runFallEvent();
	void makeNewDetail();

};

