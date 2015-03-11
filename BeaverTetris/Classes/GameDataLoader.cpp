#include "GameDataLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "KeysForEnumsDataSource.h"
#include "TetraminosFactory.h"
#include "GamePlayersDatabase.h"

GameDataLoader::GameDataLoader(void)
{
}


GameDataLoader::~GameDataLoader(void)
{
}

void GameDataLoader::loadResources()
{
	GameLevelsDataSource *gameLevelsDataSource = new GameLevelsDataSource();
	ServiceLocator::setServiceForKey(gameLevelsDataSource, gameLevelsDataSourceKey);

	CurrentPlayerDataSource *currentPlayerDataSource = new CurrentPlayerDataSource(gameLevelsDataSource);
	ServiceLocator::setServiceForKey(currentPlayerDataSource, currentPlayerDataSourceKey);

	KeysForEnumsDataSource *keysForEnumsDataSource = new KeysForEnumsDataSource();
	ServiceLocator::setServiceForKey(keysForEnumsDataSource, keysForEnumsDataSourceKey);

	TetraminosFactory *tetrominosFactory = new TetraminosFactory();
	ServiceLocator::setServiceForKey(tetrominosFactory, tetrominosFactoryKey);

	GamePlayersDatabase *gamePlayersDatabase = new GamePlayersDatabase();
	ServiceLocator::setServiceForKey(gamePlayersDatabase, gamePlayersDatabaseKey);

}