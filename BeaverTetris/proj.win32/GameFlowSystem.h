#pragma once

#include "GameSystemInterface.h"
#include "CurrentDetailController.h"
#include "CurrentGameEventsDataSource.h"
#include "ActiveDetails.h"

class GameFlowSystem: public GameSystemInterface
{
public:
	GameFlowSystem(CurrentDetailController *aCurrentDetailController, CurrentGameEventsDataSource *aCurrentGameEventsDataSource);
	~GameFlowSystem(void);

	void updateSystem(float deltaTime);

private: 

	CurrentDetailController *_currentDetailController;
	CurrentGameEventsDataSource *_currentGameEventsDataSource;
	ActiveDetails *_activeDetails;

};

