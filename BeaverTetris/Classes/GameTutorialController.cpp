#include "GameTutorialController.h"
#include "GameWorldController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "CurrentLevelDataSource.h"
#include "GameTutorialsFactory.h"

using namespace cocos2d;

GameTutorialController::GameTutorialController(GameWorldController *aGameWorld)
{
	_gameWorldController = aGameWorld;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_currentLevelName = getCurrentLevelName();
	GameTutorialsFactory *gameTutorialsFactory = new GameTutorialsFactory(this);
	_gameTutorialsFactory = gameTutorialsFactory;
	this->addChild(gameTutorialsFactory);
}


GameTutorialController::~GameTutorialController(void)
{
}

string GameTutorialController::getCurrentLevelName()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	string currentLevelName = currentLevelDataSource->getCurrentLevelData().levelName;
	return currentLevelName;
}

void GameTutorialController::onEnterTransitionDidFinish()
{
	if (_gameTutorialsFactory->availableTutorialForLevel(_currentLevelName))
	{
		startTutorial();
	}
	else
	{
		_gameWorldController->startGame();
	}
	
}

void GameTutorialController::startTutorial()
{
	if (_currentPlayerDataSource->isPlayerCompletTutorial(_currentLevelName))
	{
		_gameWorldController->startGame();
	}
	else
	{
		_gameTutorialsFactory->startTutorialForLevel(_currentLevelName);
	}
}

void GameTutorialController::endTutorial()
{
	_currentPlayerDataSource->completTutorial(_currentLevelName);
	_gameWorldController->startGame();
}