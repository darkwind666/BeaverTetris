#pragma once

#include "GameStructures.h"
#include "GameEnums.h"

class GameEventsFactory
{
public:
	GameEventsFactory(void);
	~GameEventsFactory(void);

	static GameEvent makeGoToSceneEventWithKey(GameState aKey);
	static GameEvent makeGoToPopUpEventWithKey(PopUpType aKey);
	static GameEvent makePlayerActionInGameEventWithKey(PlayerActionInGameType aKey);

};

