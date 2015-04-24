#include "GamesDevelopersAnimationController.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"
#include "GamesDevelopersBoardController.h"

using namespace cocos2d;

GamesDevelopersAnimationController::GamesDevelopersAnimationController(void)
{
	GamesDevelopersBoardController *developersBoardController = new GamesDevelopersBoardController();
	_gamesDevelopersBoard = developersBoardController;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developersBoardController, this, gameDevelopersBoardControllerKey);

	Sprite *underWaterBoardPart = CocosNodesHelper::getSpriteWithKey(gameDevelopersBoardUnderWaterPartKey);
	_underWaterBoardPart = underWaterBoardPart;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(underWaterBoardPart, this, gameDevelopersBoardUnderWaterPartKey);

	Node *gameDevelopersBeaver = CocosNodesHelper::getSpriteWithKey(gameDevelopersBeaverKey);
	gameDevelopersBeaver->setScale(0.8f);
	_gamesDevelopersBeaver = gameDevelopersBeaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameDevelopersBeaver, this, gameDevelopersBeaverKey);

	Node *gameRecordsBeaverClock = CocosNodesHelper::getSpriteWithKey(gameDevelopersClockKey);
	gameRecordsBeaverClock->setAnchorPoint(Vec2(0.5f, 1.0f));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameRecordsBeaverClock, gameDevelopersBeaver, gameDevelopersClockKey);

}

GamesDevelopersAnimationController::~GamesDevelopersAnimationController(void)
{
}

void GamesDevelopersAnimationController::onEnterTransitionDidFinish()
{
	FiniteTimeAction *actionWithDevelopersBoard = getAnimationWithBoard();
	FiniteTimeAction *actionWithDevelopersBoardUnderWaterPart = getAnimationWithBoardUnderWaterPart();
	FiniteTimeAction *spawn = Spawn::create(actionWithDevelopersBoard, actionWithDevelopersBoardUnderWaterPart, NULL);
	FiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();
	Action *sequence = Sequence::create(spawn, actionWithBeaver, NULL);
	this->runAction(sequence);
}

FiniteTimeAction* GamesDevelopersAnimationController::getAnimationWithBoard()
{
	Vec2 finalBoardPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameDevelopersBoardControllerKey);
	ActionInterval *moveBoard = MoveTo::create(gameDevelopersBoardActionDuration, finalBoardPosition);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesDevelopersBoard, moveBoard);
	return actionWithBoard;
}

FiniteTimeAction* GamesDevelopersAnimationController::getAnimationWithBoardUnderWaterPart()
{
	Vec2 finalBoardPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameDevelopersBoardUnderWaterPartKey);
	ActionInterval *moveBoard = MoveTo::create(gameDevelopersBoardActionDuration, finalBoardPosition);
	FiniteTimeAction *actionWithBoardUnderWaterPart = TargetedAction::create(_underWaterBoardPart, moveBoard);
	return actionWithBoardUnderWaterPart;
}

FiniteTimeAction* GamesDevelopersAnimationController::getAnimationWithBeaver()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameDevelopersBeaverKey);
	ActionInterval *moveBeaver = MoveTo::create(gameDevelopersBeaverActionDuration, finalBeaverPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBeaver);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesDevelopersBeaver, ease);
	return actionWithBoard;
}