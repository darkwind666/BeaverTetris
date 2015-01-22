#include "GameDataLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "KeysForEnumsDataSource.h"

GameDataLoader::GameDataLoader(void)
{
}


GameDataLoader::~GameDataLoader(void)
{
}

void GameDataLoader::loadResources()
{
	CurrentPlayerDataSource *currentPlayerDataSource = new CurrentPlayerDataSource();
	ServiceLocator::setServiceForKey(currentPlayerDataSource, currentPlayerDataSourceKey);

	GameLevelsDataSource *gameLevelsDataSource = new GameLevelsDataSource();
	ServiceLocator::setServiceForKey(gameLevelsDataSource, gameLevelsDataSourceKey);

	KeysForEnumsDataSource *keysForEnumsDataSource = new KeysForEnumsDataSource();
	ServiceLocator::setServiceForKey(keysForEnumsDataSource, keysForEnumsDataSourceKey);

}