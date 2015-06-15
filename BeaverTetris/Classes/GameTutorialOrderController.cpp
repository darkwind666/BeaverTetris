#include "GameTutorialOrderController.h"
#include "GameTutorial.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameTutorialBeaverTalkController.h"
#include "GameElementsDataHelper.h"

using namespace cocos2d;

GameTutorialOrderController::GameTutorialOrderController(GameTutorial *aGameTutorial)
{
	_gameTutorial = aGameTutorial;
	_availableTutorials = true;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(aGameTutorial, this, gameTutorialViewKey);

	GameTutorialBeaverTalkController *tutorialBeaver = new GameTutorialBeaverTalkController();
	_tutorialBeaver = tutorialBeaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(tutorialBeaver, this, gameTutorialBeaverKey);
	_startBeaverPosition = tutorialBeaver->getPosition();
	_beaverAnimationFinished = true;

	setUpKeyboard();
	_listner = getListner();
}

GameTutorialOrderController::~GameTutorialOrderController(void)
{
	_eventDispatcher->removeEventListener(_listner);
}

void GameTutorialOrderController::setUpKeyboard()
{
	EventListenerKeyboard *keyboardListner = EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(GameTutorialOrderController::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
}

EventListenerTouchOneByOne* GameTutorialOrderController::getListner()
{
	EventListenerTouchOneByOne *listner = EventListenerTouchOneByOne::create();
	listner->setSwallowTouches(false);
	listner->onTouchBegan = [](Touch *touch, Event *aEvent){return true;};
	listner->onTouchEnded = [this](Touch *touch, Event *aEvent){nextTutorial();};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);
	return listner;
}

void GameTutorialOrderController::startTutorial()
{
	_gameTutorial->startTutorial();
	Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialBeaverKey);
	ActionInterval *moveBeaver = MoveTo::create(0.3f, finalActionPosition);
	_tutorialBeaver->runAction(moveBeaver);
}

void GameTutorialOrderController::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	if (aKeyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		nextTutorial();
	}
}

void GameTutorialOrderController::nextTutorial()
{
	if (_availableTutorials == true && _beaverAnimationFinished == true)
	{
		_gameTutorial->nextTutorial();
		_availableTutorials = _gameTutorial->availableTutorials();
		_beaverAnimationFinished = false;
		FiniteTimeAction *beaverAnimation = getBeaverAnimation();
		FiniteTimeAction *callback = CallFunc::create([this](){_beaverAnimationFinished = true;});
		FiniteTimeAction *sequence = Sequence::create(beaverAnimation, callback, nullptr);
		_tutorialBeaver->runAction(sequence);
	}
}

ActionInterval* GameTutorialOrderController::getBeaverAnimation()
{
	ActionInterval *beaverAction; 
	if (_availableTutorials)
	{
		beaverAction = getNextTutorialBeaverAnimation();
	}
	else
	{
		beaverAction = MoveTo::create(0.3f, _startBeaverPosition);
	}
	return beaverAction;
}

ActionInterval* GameTutorialOrderController::getNextTutorialBeaverAnimation()
{
	ActionInterval *moveBack = MoveTo::create(0.3f, _startBeaverPosition);
	ActionInterval *delay = DelayTime::create(0.7f);
	ActionInterval *moveOnScreen = MoveTo::create(0.3f, _tutorialBeaver->getPosition());
	ActionInterval *sequence = Sequence::create(moveBack, delay, moveOnScreen, nullptr);
	return sequence;
}
