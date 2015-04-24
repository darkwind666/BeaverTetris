#include "GamesRecordsAnimationController.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GamesRecordsBoardController.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

GamesRecordsAnimationController::GamesRecordsAnimationController(void)
{
	GamesRecordsBoardController *gamesRecordsBoardController = new GamesRecordsBoardController();
	_gamesRecordsBoard = gamesRecordsBoardController;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gamesRecordsBoardController, this, gameRecordsBoardControllerKey);

	Sprite *underWaterBoardPart = CocosNodesHelper::getSpriteWithKey(gameRecordsBoardUnderWaterPartKey);
	_underWaterBoardPart = underWaterBoardPart;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(underWaterBoardPart, this, gameRecordsBoardUnderWaterPartKey);

	Node *gameRecordsBeaver = CocosNodesHelper::getSpriteWithKey(gameRecordsBeaverKey);
	_gamesRecordsBeaver = gameRecordsBeaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameRecordsBeaver, this, gameRecordsBeaverKey);

	Node *gameRecordsBeaverClock = CocosNodesHelper::getSpriteWithKey(gameRecordsClockKey);
	gameRecordsBeaverClock->setAnchorPoint(Vec2(0.0f, 0.0f));
	_gamesRecordsBeaverClock = gameRecordsBeaverClock;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameRecordsBeaverClock, gameRecordsBeaver, gameRecordsClockKey);
	runAnimationWithBeaverClock();

}


GamesRecordsAnimationController::~GamesRecordsAnimationController(void)
{
}

void GamesRecordsAnimationController::runAnimationWithBeaverClock()
{
	ActionInterval *rotateClock = RotateTo::create(0.8f, -50.0f);
	ActionInterval *rotateClockBack = RotateTo::create(0.8f, 10.0f);
	ActionInterval *sequence = Sequence::create(rotateClock, rotateClockBack, NULL);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	_gamesRecordsBeaverClock->runAction(repeat);
}

void GamesRecordsAnimationController::onEnterTransitionDidFinish()
{
	FiniteTimeAction *actionWithRecordBoard = getAnimationWithBoard();
	FiniteTimeAction *actionWithRecordBoardUnderWaterPart = getAnimationWithBoardUnderWaterPart();
	FiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();
	Action *sequence = Sequence::create(actionWithRecordBoard, actionWithRecordBoardUnderWaterPart, actionWithBeaver, NULL);
	this->runAction(sequence);
}

FiniteTimeAction* GamesRecordsAnimationController::getAnimationWithBoard()
{
	Vec2 finalBoardPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsBoardControllerKey);
	ActionInterval *moveBoard = MoveTo::create(gameRecordsBoardActionDuration, finalBoardPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBoard);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesRecordsBoard, ease);
	return actionWithBoard;
}

FiniteTimeAction* GamesRecordsAnimationController::getAnimationWithBoardUnderWaterPart()
{
	Vec2 finalBoardPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsBoardUnderWaterPartKey);
	ActionInterval *moveBoard = MoveTo::create(gameRecordsBoardActionDuration, finalBoardPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBoard);
	FiniteTimeAction *actionWithBoardUnderWaterPart = TargetedAction::create(_underWaterBoardPart, ease);
	return actionWithBoardUnderWaterPart;
}

FiniteTimeAction* GamesRecordsAnimationController::getAnimationWithBeaver()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsBeaverKey);
	ActionInterval *moveBeaver = MoveTo::create(gameRecordsBeaverActionDuration, finalBeaverPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBeaver);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesRecordsBeaver, ease);
	return actionWithBoard;
}

void GamesRecordsAnimationController::onExitTransitionDidStart()
{
	_gamesRecordsBeaverClock->stopAllActions();
}
