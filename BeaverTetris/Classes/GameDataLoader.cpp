#include "GameDataLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"

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


}