#include "GameLogicLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"

#include "GameBoard.h"
#include "GameTimeStepController.h"
#include "CurrentDetailDataSource.h"
#include "CurrentDetailController.h"
#include "FullLineCombination.h"
#include "SimilarTetraminosCombination.h"
#include "TetrisLogicSystem.h"
#include "FillingGapInBoardSystem.h"
#include "CurrentLevelDataSource.h"
#include "GameFlowSystem.h"
#include "CurrentVictoryConditionDataSource.h"
#include "WinGameSystem.h"
#include "SpellBox.h"
#include "NewTetraminoDetailDataSource.h"
#include "BossMovementObserver.h"

GameLogicLoader::GameLogicLoader(void)
{
}


GameLogicLoader::~GameLogicLoader(void)
{
}

void GameLogicLoader::loadResources()
{

	CurrentLevelDataSource *currentLevelDataSource = new CurrentLevelDataSource();
	ServiceLocator::setServiceForKey(currentLevelDataSource, currentLevelDataSourceKey);

	NewTetraminoDetailDataSource *newTetraminoDetailDataSource = new NewTetraminoDetailDataSource(currentLevelDataSource);
	ServiceLocator::setServiceForKey(newTetraminoDetailDataSource, newTetraminoDetailDataSourceKey);

	CurrentDetailDataSource *currentDetailDataSource = new CurrentDetailDataSource(newTetraminoDetailDataSource);
	ServiceLocator::setServiceForKey(currentDetailDataSource, currentDetailDataSourceKey);

	GameBoard *gameBoard = new GameBoard(tetrisBlocksWidth, tetrisBlocksHeight);
	ServiceLocator::setServiceForKey(gameBoard, gameBoardKey);

	SpellBox *spellBox = new SpellBox();
	ServiceLocator::setServiceForKey(spellBox, spellBoxKey);

	BossMovementObserver *bossMovementObserver = new BossMovementObserver();
	ServiceLocator::setServiceForKey(bossMovementObserver, bossMovementObserverKey);

	CurrentVictoryConditionDataSource *currentVictoryConditionDataSource = new CurrentVictoryConditionDataSource(currentLevelDataSource);
	ServiceLocator::setServiceForKey(currentVictoryConditionDataSource, currentVictoryConditionDataSourceKey);

	setUpMainGameLogic();
}

void GameLogicLoader::setUpMainGameLogic()
{
	GameTimeStepController *gameTimeStepController = new GameTimeStepController();
	ServiceLocator::setServiceForKey(gameTimeStepController, gameTimeStepControllerKey);
	
	GameFlowSystem *gameFlowSystem = new GameFlowSystem(gameTimeStepController);
	gameTimeStepController->addSystem(gameFlowSystem);
	
	WinGameSystem *winGameSystem = new WinGameSystem();
	gameTimeStepController->addSystem(winGameSystem);
	ServiceLocator::setServiceForKey(winGameSystem, winGameSystemKey);
	
	CurrentDetailController *currentDetailController = new CurrentDetailController();
	gameTimeStepController->addSystem(currentDetailController);
	ServiceLocator::setServiceForKey(currentDetailController, currentDetailControllerKey);
	
	TetrisLogicSystem *tetrisLogicSystem = new TetrisLogicSystem();
	gameTimeStepController->addSystem(tetrisLogicSystem);
	ServiceLocator::setServiceForKey(tetrisLogicSystem, tetrisLogicSystemKey);
}