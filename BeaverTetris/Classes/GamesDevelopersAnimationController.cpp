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

	Node *gameDevelopersBeaver = getGameDevelopersBeaver();
	_gamesDevelopersBeaver = gameDevelopersBeaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameDevelopersBeaver, this, gameDevelopersBeaverKey);

}

Node* GamesDevelopersAnimationController::getGameDevelopersBeaver()
{
	Sprite *beaver = Sprite::create("HelloWorld.png");
	beaver->setScaleX(0.2f);
	beaver->setScaleY(0.2f);
	beaver->setRotation(30);
	beaver->setColor(Color3B::GREEN);
	return beaver;
}

GamesDevelopersAnimationController::~GamesDevelopersAnimationController(void)
{
}

void GamesDevelopersAnimationController::onEnterTransitionDidFinish()
{
	FiniteTimeAction *actionWithRecordBoard = getAnimationWithBoard();
	FiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();
	Action *sequence = Sequence::create(actionWithRecordBoard, actionWithBeaver, NULL);
	this->runAction(sequence);
}

FiniteTimeAction* GamesDevelopersAnimationController::getAnimationWithBoard()
{
	Vec2 finalBoardPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameDevelopersBoardControllerKey);
	ActionInterval *moveBoard = MoveTo::create(gameDevelopersBoardActionDuration, finalBoardPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveBoard);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesDevelopersBoard, ease);
	return actionWithBoard;
}

FiniteTimeAction* GamesDevelopersAnimationController::getAnimationWithBeaver()
{

	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameDevelopersBeaverKey);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(-10,93);
	bezier.controlPoint_2 = Vec2(-20,163);
	bezier.endPosition = finalBeaverPosition;
	ActionInterval *moveBeaver = BezierTo::create(gameDevelopersBeaverActionDuration, bezier);
	FiniteTimeAction *actionWithBoard = TargetedAction::create(_gamesDevelopersBeaver, moveBeaver);
	return actionWithBoard;
}