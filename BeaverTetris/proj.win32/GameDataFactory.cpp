#include "GameDataFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GamePlayersDatabase.h"
#include "GameLevelsDataSource.h"
#include "TetraminosCharacteristicsDataSource.h"

#include "StartGameMenuDataSource.h"

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
	ServiceLocator::setServiceForKey(_tetraminosCharacteristicsDataSource, gameLevelsDataSourceKey);

}

void GameDataFactory::createGameLogic(void) 
{
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	StartGameMenuDataSource *startGameMenuDataSource = new StartGameMenuDataSource(_currentPlayerDataSource, gameViewElementsDataSource);





	ServiceLocator::setServiceForKey(startGameMenuDataSource, startGameMenuDataSourceKey);

}
