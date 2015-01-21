#include "GameInitiator.h"

#include "GameViewElementsDataSource.h"
#include "GameGraphicsLoader.h"
#include "ScenesFactory.h"
#include "ScenesTransitionsFactory.h"
#include "GameTransitionsViewController.h"
#include "GamePopUpsController.h"
#include "GameServicesKeys.h"
#include "ServiceLocator.h"

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
	
	ServiceLocator::setServiceForKey(gameViewElementsDataSource,gameViewElementsDataSourceKey);
	ServiceLocator::setServiceForKey(gameGraphicsLoader,gameGraphicsLoaderKey);
	ServiceLocator::setServiceForKey(gameTransitionsViewController,gameTransitionsViewControllerKey);
	ServiceLocator::setServiceForKey(gamePopUpsController, gamePopUpsControllerKey);

	gameGraphicsLoader->setInitialGraphic();
	gameTransitionsViewController->goToInitialState();
	
}
