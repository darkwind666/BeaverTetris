#include "GameInitiator.h"

#include "GameViewElementsDataSource.h"
#include "GameGraphicsLoader.h"
#include "ScenesFactory.h"
#include "ScenesTransitionsFactory.h"
#include "GameTransitionsViewController.h"
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

	ServiceLocator::setServiceForKey(gameViewElementsDataSource,gameViewElementsDataSourceKey);
	ServiceLocator::setServiceForKey(gameGraphicsLoader,gameGraphicsLoaderKey);

	/*
	GameTransitionsViewController *gameTransitionsViewController = getGameTransitionsViewController();

	ServiceLocator::setServiceForKey(gameTransitionsViewController,gameTransitionsViewControllerKey);

	gameGraphicsLoader->setInitialGraphic();
	gameTransitionsViewController->goToInitialState();
	*/
}

GameTransitionsViewController* GameInitiator::getGameTransitionsViewController()
{
	ScenesFactory *scenesFactory = new ScenesFactory();
	ScenesTransitionsFactory *scenesTransitionsFactory = new ScenesTransitionsFactory();
	GameTransitionsViewController *gameTransitionsViewController = new GameTransitionsViewController(scenesTransitionsFactory, scenesFactory);
	return gameTransitionsViewController;
}