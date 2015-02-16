#include "ExplosionAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "AnimationSynchonizer.h"
#include "TetraminoExplosionFactory.h"
#include "GameBoard.h"

#include "DamageToPlayerSpell.h"
#include "SimilarTetraminosCombination.h"
#include "FullLineCombination.h"

using namespace cocos2d;
using namespace std;

ExplosionAnimationController::ExplosionAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	setUpDelegates();
	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	this->addChild(_tetraminoExplosionFactory);
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}


ExplosionAnimationController::~ExplosionAnimationController(void)
{
}

void ExplosionAnimationController::setUpDelegates()
{
	ServiceInterface *service = ServiceLocator::getServiceForKey(damageToPlayerSpellModelKey);
	if (service)
	{
		DamageToPlayerSpell *damageToPlayerSpellModel = (DamageToPlayerSpell*)service;
		damageToPlayerSpellModel->setDelegate(this);
	}

	SimilarTetraminosCombination *similarTetraminosCombinationModel = (SimilarTetraminosCombination*)ServiceLocator::getServiceForKey(similarTetraminosCombinationModelKey);
	similarTetraminosCombinationModel->setDelegate(this);

	FullLineCombination *fullLineCombinationModel = (FullLineCombination*)ServiceLocator::getServiceForKey(fullLineCombinationModelKey);
	fullLineCombinationModel->setDelegate(this);
}

void ExplosionAnimationController::blowUpTetraminosForPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = getTetraminosExplosionsAnimation(tetraminosPositions);
	FiniteTimeAction *sequence = _tetraminoExplosionFactory->getTetraminosExplosionAnimationWithAction(tetraminosLineExplosionAnimation);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* ExplosionAnimationController::getTetraminosExplosionsAnimation(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create([this, tetraminosPositions](){
		vector<Node*> explosions = getExplosionsFromPositions(tetraminosPositions);
		_tetraminoExplosionFactory->addExplosionsToView(explosions);
	});
	return tetraminosLineExplosionAnimation;
}

vector<Node*> ExplosionAnimationController::getExplosionsFromPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	vector<Node*> explosions;
	vector<GamePositionOnBoard>::iterator positionIterator;
	for (positionIterator = tetraminosPositions.begin(); positionIterator != tetraminosPositions.end(); positionIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionIterator;
		Node *explosion = _tetraminoExplosionFactory->getExplosionForOnPositionXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		explosions.push_back(explosion);
	}
	return explosions;
}

void ExplosionAnimationController::blowUpLine(int aLineIndex)
{
	vector<GamePositionOnBoard> tetraminosPositionsInLine = getTetraminosPositionsInLine(aLineIndex);
	blowUpTetraminosForPositions(tetraminosPositionsInLine);
}

vector<GamePositionOnBoard> ExplosionAnimationController::getTetraminosPositionsInLine(int aLineIndex)
{
	vector<GamePositionOnBoard> positionsInLine;
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < gameBoardWidth; widthIndex++)
	{
		GamePositionOnBoard position;
		position.xPosition = widthIndex;
		position.yPosition = aLineIndex;
		positionsInLine.push_back(position);
	}
	return positionsInLine;
}

void ExplosionAnimationController::removeTetraminoOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = _tetraminoExplosionFactory->getRemoveTetraminoActionOnPositionXY(xPosition, yPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithTetraminoView);
}

void ExplosionAnimationController::setCallback(function<void()> aCallback)
{
	FiniteTimeAction *endCallback = _tetraminoExplosionFactory->getCallbackAction(aCallback);
	_animationSynchonizer->addAnimationToQueue(endCallback);
}