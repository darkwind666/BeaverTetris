#include "GameLogicLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"

#include "GameBoard.h"
#include "GameTimeStepController.h"
#include "CurrentDetailDataSource.h"
#include "CurrentDetailController.h"

GameLogicLoader::GameLogicLoader(void)
{
}


GameLogicLoader::~GameLogicLoader(void)
{
}

void GameLogicLoader::loadResources()
{
	GameBoard *gameBoard = new GameBoard(tetrisBlocksWidth, tetrisBlocksHeight);
	ServiceLocator::setServiceForKey(gameBoard, gameBoardKey);

	GameTimeStepController *gameTimeStepController = new GameTimeStepController();
	ServiceLocator::setServiceForKey(gameTimeStepController, gameTimeStepControllerKey);

	CurrentDetailDataSource *currentDetailDataSource = new CurrentDetailDataSource();
	ServiceLocator::setServiceForKey(currentDetailDataSource, currentDetailDataSourceKey);

	CurrentDetailController *currentDetailController = new CurrentDetailController(gameBoard, currentDetailDataSource);
	ServiceLocator::setServiceForKey(currentDetailController, currentDetailControllerKey);

}