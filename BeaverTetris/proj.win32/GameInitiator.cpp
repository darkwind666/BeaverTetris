#include "GameInitiator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "GameTransitionsController.h"
#include "GameGraphicsDataSource.h"
#include "GameViewInformationFactory.h"

GameInitiator::GameInitiator() 
{
	_gameViewElementsDataSource = new GameViewElementsDataSource;
	_gameTransitionsController = new GameTransitionsController;

}

GameInitiator::~GameInitiator()
{

}

void GameInitiator::setInitialState()
{

	GameViewInformationFactory viewInformationFactory;
	viewInformationFactory.setGameElementsInformationInDataSource(_gameViewElementsDataSource);

	ServiceLocator::setServiceForKey(_gameViewElementsDataSource,gameViewElementsDataSourceKey);
	ServiceLocator::setServiceForKey(_gameTransitionsController,gameTransitionsControllerKey);

	GameGraphicsDataSource gameGraphicsDataSource;
	gameGraphicsDataSource.getInitialGraphic();

}