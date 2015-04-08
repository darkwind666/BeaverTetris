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

	Node *gameRecordsBeaver = getGameRecordsBeaver();
	_gamesRecordsBeaver = gameRecordsBeaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameRecordsBeaver, this, gameRecordsBeaverKey);
}


GamesRecordsAnimationController::~GamesRecordsAnimationController(void)
{
}

Node* GamesRecordsAnimationController::getGameRecordsBeaver()
{
	Sprite *beaver = Sprite::create("HelloWorld.png");
	beaver->setScaleX(0.2f);
	beaver->setScaleY(0.7f);
	beaver->setRotation(0);
	beaver->setColor(Color3B::BLUE);
	return beaver;
}

void GamesRecordsAnimationController::onEnterTransitionDidFinish()
{
	FiniteTimeAction *actionWithRecordBoard = getAnimationWithBoard();
	FiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();
	Action *sequence = Sequence::create(actionWithRecordBoard, actionWithBeaver, NULL);
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

FiniteTimeAction* GamesRecordsAnimationController::getAnimationWithBeaver()
{

	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsBeaverKey);
	ActionInterval *moveBeaver = MoveTo::create(gameRecordsBeaverActionDuration, finalBeaverPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBeaver);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesRecordsBeaver, ease);
	return actionWithBoard;
}
