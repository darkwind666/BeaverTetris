#include "GameInitiator.h"
#include "ServiceLocator.h"
#include "GameViewElementsDataSource.h"
#include "GameTransitionsController.h"
#include "GameGraphicsDataSource.h"

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
	ServiceLocator::setGameViewElementsDataSource(_gameViewElementsDataSource);
	ServiceLocator::setGameTransitionsController(_gameTransitionsController);

	GameGraphicsDataSource gameGraphicsDataSource;
	gameGraphicsDataSource.getInitialGraphic();

}