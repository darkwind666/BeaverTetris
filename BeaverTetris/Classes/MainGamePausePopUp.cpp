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

using namespace cocos2d;

MainGamePausePopUp::MainGamePausePopUp(GameWorldController *aGameWorldController)
{
	ScreenPopUp::subscribePopUpToMessage(this, kPauseGamePopUp);
	_gameWorldController = aGameWorldController;
	_mainGamePauseDelegate = (MainGamePauseDelegate*)ServiceLocator::getServiceForKey(mainGamePauseDelegateKey);
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_popUpView = makePopUpView();
	setUpKeyboard();
}


MainGamePausePopUp::~MainGamePausePopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kPauseGamePopUp);
}

CCNode* MainGamePausePopUp::makePopUpView()
{

	CCLayerColor *popUpPad = CCLayerColor::create(Color4B::RED, 300, 200);
	popUpPad->ignoreAnchorPointForPosition(false);

	GameSoundEffectsRegulator *soundEffectsRegulator = new GameSoundEffectsRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(soundEffectsRegulator,popUpPad,mainGamePauseRegulateSoundEffectsSliderKey);

	GameBackgroundSoundRegulator *backgroundSoundRegulator = new GameBackgroundSoundRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundSoundRegulator,popUpPad,mainGamePauseRegulateSoundSliderKey);

	CCMenuItemImage *closeButtonItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(MainGamePausePopUp::closePopUp, this));
	closeButtonItem->setScaleX(0.2f);
	closeButtonItem->setScaleY(0.07f);
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButtonItem,popUpPad,mainGamePauseCloseButtonKey);

	CCMenuItemImage *goToSelectLevelItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png", CC_CALLBACK_1(MainGamePausePopUp::goToSelectLevelScreen, this));
	goToSelectLevelItem->setScaleX(0.2f);
	goToSelectLevelItem->setScaleY(0.07f);
	goToSelectLevelItem->setColor(ccColor3B::GREEN);
	CocosNodesHelper::addButtonToParentNodeWithKey(goToSelectLevelItem,popUpPad,mainGamePauseGoToSelectLevelButtonKey);

	CocosNodesHelper::addChildNodeToParentNodeWithKey(popUpPad,this,mainGamePausePadKey);

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

void MainGamePausePopUp::closePopUp(CCObject* pSender)
{
	CCNode *button = (CCNode*)pSender;
	std::function<void()> buttonCallback = [this](){hidePopUp();};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}

void MainGamePausePopUp::goToSelectLevelScreen(CCObject* pSender)
{
	CCNode *button = (CCNode*)pSender;
	std::function<void()> buttonCallback = [](){
		StartMainGamePlayerScoreDataSource *startPlayerScoreDataSource = (StartMainGamePlayerScoreDataSource*)ServiceLocator::getServiceForKey(startMainGamePlayerScoreDataSourceKey);
		startPlayerScoreDataSource->restorePlayerScore();
		GameStatesHelper::goToScene(kSelectLevel);
	};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}

void MainGamePausePopUp::hidePopUp()
{
	FiniteTimeAction *moveController = CCMoveTo::create(regulateSoundPopUpStartDisapperDuration, _oldControllerPosition);
	FiniteTimeAction *moveCallback = CallFunc::create([this](){
		_eventListenerKeyboard->setEnabled(false);
		_mainGamePauseDelegate->endPause();
		_gameTimeStepController->setUpdateAvailable(true);
		_gameWorldController->resumeGameWorld();
	});
	FiniteTimeAction *sequence = Sequence::create(moveController, moveCallback, NULL);
	_popUpView->runAction(sequence);
}

void MainGamePausePopUp::showPopUp()
{
	_gameWorldController->pauseGameWorld();
	_eventListenerKeyboard->setEnabled(true);
	_oldControllerPosition = _popUpView->getPosition();
	Vec2 newControllerPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(mainGamePausePadKey);
	CCActionInterval *moveController = CCMoveTo::create(regulateSoundPopUpStartAppearDuration, newControllerPosition);
	Action *ease = CCEaseBackOut::create(moveController);
	_popUpView->runAction(ease);
}