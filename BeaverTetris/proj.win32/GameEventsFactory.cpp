#include "GameEventsFactory.h"


GameEventsFactory::GameEventsFactory(void)
{
}


GameEventsFactory::~GameEventsFactory(void)
{
}


GameEvent GameEventsFactory::makeGoToSceneEventWithKey(GameState aKey)
{
	GameEvent gameEvent;
	gameEvent.eventType = kGoToSceneEvent;
	GameEventInformation eventInformation;
	eventInformation.gameState = aKey;
	gameEvent.eventInformation = eventInformation;
	return gameEvent;
}

GameEvent GameEventsFactory::makeGoToPopUpEventWithKey(PopUpType aKey)
{
	GameEvent gameEvent;
	gameEvent.eventType = kGoToPopUp;
	GameEventInformation eventInformation;
	eventInformation.popUp = aKey;
	gameEvent.eventInformation = eventInformation;
	return gameEvent;
}

GameEvent GameEventsFactory::makePlayerActionInGameEventWithKey(PlayerActionInGameType aKey)
{
	GameEvent gameEvent;
	gameEvent.eventType = kPlayerActionInGameEvent;
	GameEventInformation eventInformation;
	eventInformation.playerAction = aKey;
	gameEvent.eventInformation = eventInformation;
	return gameEvent;
}