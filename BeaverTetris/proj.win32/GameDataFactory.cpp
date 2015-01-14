#include "GameDataFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GamePlayersDatabase.h"
#include "GameLevelsDataSource.h"
#include "TetraminosCharacteristicsDataSource.h"

#include "StartGameMenuDataSource.h"
#include "GameViewElementsDataSource.h"
#include "GamePopUpsController.h"
#include "EventDispatcher.h"
#include "GameLevelsMenuDataSource.h"

GameDataFactory::GameDataFactory(void)
{
}


GameDataFactory::~GameDataFactory(void)
{
}

void GameDataFactory::createGameData(void) 
{
	_gamePlayersDatabase = new GamePlayersDatabase;
	_currentPlayerDataSource = new CurrentPlayerDataSource(_gamePlayersDatabase);
	_gameLevelsDataSource = new GameLevelsDataSource;
	_tetraminosCharacteristicsDataSource = new TetraminosCharacteristicsDataSource;

	ServiceLocator::setServiceForKey(_gamePlayersDatabase, gamePlayersDatabaseKey);
	ServiceLocator::setServiceForKey(_currentPlayerDataSource, currentPlayerDataSourceKey);
	ServiceLocator::setServiceForKey(_gameLevelsDataSource, gameLevelsDataSourceKey);
	ServiceLocator::setServiceForKey(_tetraminosCharacteristicsDataSource, tetraminosCharacteristicsDataSourceKey);

}

void GameDataFactory::createGameLogic(void) 
{
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	StartGameMenuDataSource *startGameMenuDataSource = new StartGameMenuDataSource(_currentPlayerDataSource);

	EventDispatcher *eventDispatcher = (EventDispatcher*)ServiceLocator::getServiceForKey(eventDispatcherKey);

	GamePopUpsController *gamePopUpsController = new GamePopUpsController();
	eventDispatcher->setEventHandlerWithEventName(gamePopUpsController,kGoToPopUp);
	eventDispatcher->setEventHandlerWithEventName(gamePopUpsController,kClosePopUp);

	GameLevelsMenuDataSource *gameLevelsMenuDataSource = new GameLevelsMenuDataSource(_currentPlayerDataSource,_gameLevelsDataSource,gameViewElementsDataSource);


	ServiceLocator::setServiceForKey(startGameMenuDataSource, startGameMenuDataSourceKey);
	ServiceLocator::setServiceForKey(gameLevelsMenuDataSource, gameLevelsMenuDataSourceKey);

}
