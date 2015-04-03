#include "GameInitiator.h"
#include "GameServicesKeys.h"
#include "ServiceLocator.h"

#include "GameViewElementsDataSource.h"
#include "GameGraphicsLoader.h"
#include "ScenesFactory.h"
#include "ScenesTransitionsFactory.h"
#include "GameTransitionsViewController.h"
#include "GamePopUpsController.h"
#include "GameSoundController.h"

GameInitiator::GameInitiator() 
{
	
}

GameInitiator::~GameInitiator()
{

}

void GameInitiator::setInitialState()
{
	GameViewElementsDataSource *gameViewElementsDataSource = new GameViewElementsDataSource();
	GameGraphicsLoader *gameGraphicsLoader =  new GameGraphicsLoader();
	GameTransitionsViewController *gameTransitionsViewController = new GameTransitionsViewController();
	GamePopUpsController *gamePopUpsController = new GamePopUpsController();
	GameSoundController *gameSoundController = new GameSoundController();

	
	ServiceLocator::setServiceForKey(gameViewElementsDataSource,gameViewElementsDataSourceKey);
	ServiceLocator::setServiceForKey(gameGraphicsLoader,gameGraphicsLoaderKey);
	ServiceLocator::setServiceForKey(gameTransitionsViewController,gameTransitionsViewControllerKey);
	ServiceLocator::setServiceForKey(gamePopUpsController, gamePopUpsControllerKey);
	ServiceLocator::setServiceForKey(gameSoundController, gameSoundControllerKey);

	gameGraphicsLoader->setInitialGraphic();
	gameTransitionsViewController->goToInitialState();
	
}
