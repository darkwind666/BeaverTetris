#include "ExplosionAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "AnimationSynchonizer.h"
#include "TetraminoExplosionFactory.h"
#include "GameBoard.h"

#include "DamageToPlayerSpell.h"
#include "SimilarTetraminosCombination.h"
#include "FullLineCombination.h"
#include "RandomExplosionsSpell.h"

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

	RandomExplosionsSpell *randomExplosionsSpellModel = (RandomExplosionsSpell*)ServiceLocator::getServiceForKey(randomExplosionsSpellModelKey);
	randomExplosionsSpellModel->setDelegate(this);
}

void ExplosionAnimationController::blowUpTetraminosForPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = _tetraminoExplosionFactory->getTetraminosExplosionsAnimationWithPositions(tetraminosPositions);
	_animationSynchonizer->addAnimationToQueue(tetraminosLineExplosionAnimation);
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