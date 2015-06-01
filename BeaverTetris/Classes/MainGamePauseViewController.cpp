#include "MainGamePauseViewController.h"
#include "GameViewStyleHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "GameAnimationActionsConstants.h"
#include "WinGameSystem.h"
#include "MainGamePauseDelegate.h"
#include "GameStatesHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

MainGamePauseViewController::MainGamePauseViewController(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	setPauseView();
	setUpKeyboard();

	MainGamePauseDelegate *mainGamePauseDelegate = (MainGamePauseDelegate*)ServiceLocator::getServiceForKey(mainGamePauseDelegateKey);
	mainGamePauseDelegate->addObserver(this);
}


MainGamePauseViewController::~MainGamePauseViewController(void)
{
}

void MainGamePauseViewController::setUpKeyboard()
{
	cocos2d::EventListenerKeyboard *keyboardListner = cocos2d::EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(MainGamePauseViewController::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
	_eventListenerKeyboard = keyboardListner;
}

void MainGamePauseViewController::setPauseView()
{
	Sprite *pauseViewActiveImage = CocosNodesHelper::getSpriteWithKey(pauseGameViewControllerKey);
	Sprite *pauseViewInactiveImage = CocosNodesHelper::getSpriteWithKey(pauseGameViewControllerKey);
	MenuItemSprite *pauseButtonItem = MenuItemSprite::create(pauseViewActiveImage,pauseViewInactiveImage,[this](Ref*){stopGame();});
	CocosNodesHelper::addButtonToParentNodeWithKey(pauseButtonItem, this, playerSpellImageKey);
	_pauseView = pauseButtonItem;

	Node *pauseButtonLabel = getPauseButtonLabel();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(pauseButtonLabel, this, playerSpellButtonLabelKey);
}

Node* MainGamePauseViewController::getPauseButtonLabel()
{
	Label *pauseButtonLabel = GameViewStyleHelper::getStandardLabelWithFontSize(13);
	pauseButtonLabel->setColor(Color3B(41, 104, 110));
	pauseButtonLabel->setString(string("P"));
	return pauseButtonLabel;
}

void MainGamePauseViewController::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	if (aKeyCode == EventKeyboard::KeyCode::KEY_P)
	{
		stopGame();
	}
}

void MainGamePauseViewController::stopGame()
{
	if (_winGameSystem->gameEnded() == false)
	{
		_eventListenerKeyboard->setEnabled(false);
		_gameTimeStepController->setUpdateAvailable(false);
		function<void()> callback = [](){ GameStatesHelper::goToPopUp(kPauseGamePopUp);};
		GameViewStyleHelper::runButtonActionWithCallbackAndDuration(_pauseView ,callback, gameControllButtonActionDuration);
	}
}

void MainGamePauseViewController::pauseWasEnded()
{
	_eventListenerKeyboard->setEnabled(true);
}