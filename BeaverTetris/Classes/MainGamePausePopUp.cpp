#include "MainGamePausePopUp.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameSoundEffectsRegulator.h"
#include "GameBackgroundSoundRegulator.h"
#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "MainGamePauseDelegate.h"
#include "GameWorldController.h"
#include "GameStatesHelper.h"
#include "StartMainGamePlayerScoreDataSource.h"
#include "GameAnalyticController.h"
#include "GameLocalizationKeys.h"

using namespace cocos2d;

MainGamePausePopUp::MainGamePausePopUp(GameWorldController *aGameWorldController)
{
	ScreenPopUp::subscribePopUpToMessage(this, kPauseGamePopUp);
	_gameWorldController = aGameWorldController;
	_mainGamePauseDelegate = (MainGamePauseDelegate*)ServiceLocator::getServiceForKey(mainGamePauseDelegateKey);
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_popUpView = makePopUpView();
	_popUpView->setVisible(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_popUpView,this,mainGamePauseBackgroundKey);
	setUpKeyboard();
}


MainGamePausePopUp::~MainGamePausePopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kPauseGamePopUp);
}

Node* MainGamePausePopUp::makePopUpView()
{
	Node *popUpBackground = GameViewStyleHelper::getPopUpBackground();
	CocosNodesHelper::addSpriteToParentNodeWithKey(popUpBackground,mainGamePauseBackgroundPauseLabelKey);
	Node *popUpMenu = getPopUpMenu();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(popUpMenu,popUpBackground,mainGamePausePadKey);
	return popUpBackground;
}

cocos2d::Node* MainGamePausePopUp::getPopUpMenu()
{
	Sprite *popUpPad = CocosNodesHelper::getSpriteWithKey(mainGamePausePadKey);

	GameSoundEffectsRegulator *soundEffectsRegulator = new GameSoundEffectsRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(soundEffectsRegulator,popUpPad,mainGamePauseRegulateSoundEffectsSliderKey);
	
	GameBackgroundSoundRegulator *backgroundSoundRegulator = new GameBackgroundSoundRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundSoundRegulator,popUpPad,mainGamePauseRegulateSoundSliderKey);
	
	GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallback(popUpPad, mainGamePauseCloseButtonKey, CC_CALLBACK_1(MainGamePausePopUp::closePopUp, this));
	GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallbackAndLocalization(popUpPad, mainGamePauseGoToSelectLevelButtonKey, CC_CALLBACK_1(MainGamePausePopUp::goToSelectLevelScreen, this), gameGoToMapLocalizationKey);
	
	return popUpPad;
}

void MainGamePausePopUp::setUpKeyboard()
{
	cocos2d::EventListenerKeyboard *keyboardListner = cocos2d::EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(MainGamePausePopUp::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
	keyboardListner->setEnabled(false);
	_eventListenerKeyboard = keyboardListner;
}

void MainGamePausePopUp::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	if (aKeyCode == EventKeyboard::KeyCode::KEY_P)
	{
		hidePopUp();
	}
}

void MainGamePausePopUp::closePopUp(Object* pSender)
{
	Node *button = (Node*)pSender;
	std::function<void()> buttonCallback = [this](){hidePopUp();};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}

void MainGamePausePopUp::goToSelectLevelScreen(Object* pSender)
{
	Node *button = (Node*)pSender;
	std::function<void()> buttonCallback = [](){
		StartMainGamePlayerScoreDataSource *startPlayerScoreDataSource = (StartMainGamePlayerScoreDataSource*)ServiceLocator::getServiceForKey(startMainGamePlayerScoreDataSourceKey);
		startPlayerScoreDataSource->restorePlayerScore();
		GameStatesHelper::goToScene(kSelectLevel);
	};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}

void MainGamePausePopUp::hidePopUp()
{
	FiniteTimeAction *moveCallback = CallFunc::create([this](){
		_eventListenerKeyboard->setEnabled(false);
		_mainGamePauseDelegate->endPause();
		_gameTimeStepController->setUpdateAvailable(true);
		_gameWorldController->resumeGameWorld();
		_popUpView->setVisible(false);
	});
	_popUpView->runAction(moveCallback);
}

void MainGamePausePopUp::showPopUp()
{
	_gameWorldController->pauseGameWorld();
	_eventListenerKeyboard->setEnabled(true);
	_popUpView->setVisible(true);
	GameAnalyticController *gameAnalyticController = (GameAnalyticController*)ServiceLocator::getServiceForKey(gameAnalyticControllerKey);
	gameAnalyticController->goToPopUp(kPauseGamePopUp);
}