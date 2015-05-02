#include "GameDataLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "KeysForEnumsDataSource.h"
#include "TetraminosFactory.h"
#include "GamePlayersDatabase.h"
#include "TetraminoColorsDataSource.h"
#include "GameLocalizationDataSource.h"

GameDataLoader::GameDataLoader(void)
{
}


GameDataLoader::~GameDataLoader(void)
{
}

void GameDataLoader::loadResources()
{
	KeysForEnumsDataSource *keysForEnumsDataSource = new KeysForEnumsDataSource();
	ServiceLocator::setServiceForKey(keysForEnumsDataSource, keysForEnumsDataSourceKey);

	GameLevelsDataSource *gameLevelsDataSource = new GameLevelsDataSource();
	ServiceLocator::setServiceForKey(gameLevelsDataSource, gameLevelsDataSourceKey);

	CurrentPlayerDataSource *currentPlayerDataSource = new CurrentPlayerDataSource(gameLevelsDataSource);
	ServiceLocator::setServiceForKey(currentPlayerDataSource, currentPlayerDataSourceKey);

	TetraminosFactory *tetrominosFactory = new TetraminosFactory(keysForEnumsDataSource);
	ServiceLocator::setServiceForKey(tetrominosFactory, tetrominosFactoryKey);

	GamePlayersDatabase *gamePlayersDatabase = new GamePlayersDatabase();
	ServiceLocator::setServiceForKey(gamePlayersDatabase, gamePlayersDatabaseKey);

	TetraminoColorsDataSource *tetraminoColorsDataSource = new TetraminoColorsDataSource();
	ServiceLocator::setServiceForKey(tetraminoColorsDataSource, tetraminoColorsDataSourceKey);

	GameLocalizationDataSource *gameLocalizationDataSource = new GameLocalizationDataSource();
	ServiceLocator::setServiceForKey(gameLocalizationDataSource, gameLocalizationDataSourceKey);

}