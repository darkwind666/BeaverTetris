#include "BossMovementAnimationController.h"
#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "BossMovementObserver.h"
#include "GameBoard.h"
#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "GameAnimationActionsConstants.h"
#include "TetraminoViewController.h"

using namespace cocos2d;
using namespace std;

BossMovementAnimationController::BossMovementAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_gameBoardViewDataSource = new GameBoardViewDataSource();

	BossMovementObserver *bossMovementObserver = (BossMovementObserver*)ServiceLocator::getServiceForKey(bossMovementObserverKey);
	bossMovementObserver->setDelegate(this);
}


BossMovementAnimationController::~BossMovementAnimationController(void)
{
}

void BossMovementAnimationController::moveBossFromStartPositionToFinal(GamePositionOnBoard aStartPosition, GamePositionOnBoard aFinalPosition)
{
	Node *gameBoardView = getBossViewWithStartPosition(aStartPosition);
	FiniteTimeAction *animationWithBoss = getAnimationWithBossViewAndFinalPosition(gameBoardView, aFinalPosition);
	_animationSynchonizer->addAnimationToQueue(animationWithBoss);
}

Node* BossMovementAnimationController::getBossViewWithStartPosition(GamePositionOnBoard aStartPosition)
{
	TetraminoViewController *tetraminoView = new TetraminoViewController();
	int tetraminoIndex = _gameBoard->getIndexForPosition(aStartPosition);
	_gameBoardController->cleanTetraminoOnIndex(tetraminoIndex);
	Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(tetraminoIndex);
	tetraminoView->setTexture(tetraminoTexture);
	this->addChild(tetraminoView);
	return tetraminoView;
}

FiniteTimeAction* BossMovementAnimationController::getAnimationWithBossViewAndFinalPosition(Node *aView, GamePositionOnBoard aFinalPosition)
{
	FiniteTimeAction *moveBoard = getMoveBossAnimationWithViewAndFinalPosition(aView, aFinalPosition);
	function<void(Node*)> callbackFunction = getAnimationEndCallbackWithFinalPosition(aFinalPosition);
	FiniteTimeAction *callback = CallFuncN::create(callbackFunction);
	FiniteTimeAction *sequence = Sequence::create(moveBoard,callback, NULL);
	FiniteTimeAction *animationWithTetramino = TargetedAction::create(aView,sequence);
	return animationWithTetramino;
}

FiniteTimeAction* BossMovementAnimationController::getMoveBossAnimationWithViewAndFinalPosition(Node *aView, GamePositionOnBoard aFinalPosition)
{
	int finalTetraminoPositionIndex = _gameBoard->getIndexForPosition(aFinalPosition);
	Vec2 finalBoardPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(finalTetraminoPositionIndex);
	Vec2 currentBoardPosition = aView->getPosition();
	float yDifference = finalBoardPosition.y - currentBoardPosition.y;
	float animationDuration = yDifference * fallActionDurationPerTetramino;
	float absoluteDurationValue = abs(animationDuration);
	FiniteTimeAction *moveBoss = MoveTo::create(absoluteDurationValue, finalBoardPosition);
	return moveBoss;
}

function<void(Node*)> BossMovementAnimationController::getAnimationEndCallbackWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	function<void(Node*)> callback = [this, aFinalPosition](Node *sender){
		TetraminoViewController *view = (TetraminoViewController*)sender;
		int bossTag = _gameBoard->getIndexForPosition(aFinalPosition);
		string bossName = view->getTextureName();
		_gameBoardController->drawTetraminoTextureOnIndex(bossName, bossTag);
		sender->removeFromParentAndCleanup(true);
	};
	return callback;
}