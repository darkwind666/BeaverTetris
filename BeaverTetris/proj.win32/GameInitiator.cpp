#include "GameInitiator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameStructures.h"
#include "GameViewElementsDataSource.h"
#include "EventDispatcher.h"
#include "GameTransitionsController.h"
#include "GameGraphicsDataSource.h"
#include "GameViewInformationFactory.h"

GameInitiator::GameInitiator() 
{
	_gameViewElementsDataSource = new GameViewElementsDataSource;
	_eventDispatcher = new EventDispatcher;

}

GameInitiator::~GameInitiator()
{

}

void GameInitiator::setInitialState()
{

	GameViewInformationFactory viewInformationFactory;
	viewInformationFactory.setGameElementsInformationInDataSource(_gameViewElementsDataSource);
	GameTransitionsController *gameTransitionsController = new GameTransitionsController;
	_eventDispatcher->setEventHandlerWithEventName(gameTransitionsController, kGoToSceneEvent);

	ServiceLocator::setServiceForKey(_gameViewElementsDataSource,gameViewElementsDataSourceKey);
	ServiceLocator::setServiceForKey(_eventDispatcher,eventDispatcherKey);

	GameGraphicsDataSource gameGraphicsDataSource;
	gameGraphicsDataSource.getInitialGraphic();

}