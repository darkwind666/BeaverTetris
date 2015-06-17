#include "BackButtonController.h"
#include "GameStatesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "StartMainGamePlayerScoreDataSource.h"
#include "CurrentPlayerDataSource.h"
#include "CurrentLevelDataSource.h"

using namespace cocos2d;
using namespace std;

BackButtonController::BackButtonController(GameState screenType)
{
	_screenType = screenType;
	_backButtonHandlers = getBackButtonHandlers();
	setUpKeyboard();
}


BackButtonController::~BackButtonController(void)
{
}

void BackButtonController::setUpKeyboard()
{
	EventListenerKeyboard *keyboardListner = EventListenerKeyboard::create();
	keyboardListner->onKeyReleased = CC_CALLBACK_2(BackButtonController::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
}

map< GameState, function<void()> > BackButtonController::getBackButtonHandlers()
{
	map< GameState, function<void()> > backButtonHandlers;

	backButtonHandlers[kLoadGame] = [](){Director::getInstance()->end();};
	backButtonHandlers[kStartGame] = [](){Director::getInstance()->end();};
	backButtonHandlers[kSelectLevel] = [](){GameStatesHelper::goToScene(kStartGame);};
	backButtonHandlers[kDevelopers] = [](){GameStatesHelper::goToScene(kStartGame);};
	backButtonHandlers[kRecords] = [](){GameStatesHelper::goToScene(kStartGame);};
	backButtonHandlers[kPlayGame] = [this](){backButtonInMainGamePressed();};

	return backButtonHandlers;
}

void BackButtonController::backButtonInMainGamePressed()
{
	WinGameSystem *winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	if (winGameSystem->gameEnded())
	{
		gameEndedBackButtonPressed();
	}
	else
	{
		restorePlayer();
	}
}

void BackButtonController::gameEndedBackButtonPressed()
{
	WinGameSystem *winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	if (winGameSystem->playerWin())
	{
		gameEndedWithWinResult();
		
	}
	else
	{
		restorePlayer();
	}
}

void BackButtonController::gameEndedWithWinResult()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	if (currentLevelDataSource->finalLevel())
	{
		CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
		currentPlayerDataSource->cleanPlayer();
		GameStatesHelper::goToScene(kRecords);
	}
	else
	{
		GameStatesHelper::goToScene(kSelectLevel);
	}
}

void BackButtonController::restorePlayer()
{
	StartMainGamePlayerScoreDataSource *startPlayerScoreDataSource = (StartMainGamePlayerScoreDataSource*)ServiceLocator::getServiceForKey(startMainGamePlayerScoreDataSourceKey);
	startPlayerScoreDataSource->restorePlayerScore();
	GameStatesHelper::goToScene(kSelectLevel);
}

void BackButtonController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *aEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		function<void()> backButtonHandler = _backButtonHandlers[_screenType];
		backButtonHandler();
		aEvent->stopPropagation();
	}
}
