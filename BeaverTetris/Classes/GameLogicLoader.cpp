#include "GameLogicLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "GamePopUpsController.h"

GameLogicLoader::GameLogicLoader(void)
{
}


GameLogicLoader::~GameLogicLoader(void)
{
}

void GameLogicLoader::loadResources()
{
	GamePopUpsController *gamePopUpsController = new GamePopUpsController();
	ServiceLocator::setServiceForKey(gamePopUpsController, gamePopUpsControllerKey);
}