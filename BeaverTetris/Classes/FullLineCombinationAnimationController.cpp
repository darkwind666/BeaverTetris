#include "FullLineCombinationAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FullLineCombination.h"
#include "GameBoard.h"
#include "AnimationSynchonizer.h"
#include "TetraminoExplosionFactory.h"

using namespace cocos2d;
using namespace std;

FullLineCombinationAnimationController::FullLineCombinationAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	FullLineCombination *fullLineCombinationModel = (FullLineCombination*)ServiceLocator::getServiceForKey(fullLineCombinationModelKey);
	fullLineCombinationModel->setDelegate(this);

	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	this->addChild(_tetraminoExplosionFactory);
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}

FullLineCombinationAnimationController::~FullLineCombinationAnimationController(void)
{
}

void FullLineCombinationAnimationController::blowUpLine(int aLineIndex)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = getTetraminosLineExplosionAnimation(aLineIndex);
	FiniteTimeAction *sequence = _tetraminoExplosionFactory->getTetraminosExplosionAnimationWithAction(tetraminosLineExplosionAnimation);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* FullLineCombinationAnimationController::getTetraminosLineExplosionAnimation(int aLineIndex)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create([this, aLineIndex](){
		vector<Node*> explosions = getExplosionsInLine(aLineIndex);
		_tetraminoExplosionFactory->addExplosionsToView(explosions);
	});
	return tetraminosLineExplosionAnimation;
}

vector<Node*> FullLineCombinationAnimationController::getExplosionsInLine(int aLineIndex)
{
	vector<Node*> explosions;
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < gameBoardWidth; widthIndex++)
	{
		Node *explosion = _tetraminoExplosionFactory->getExplosionForOnPositionXY(widthIndex, aLineIndex);
		explosions.push_back(explosion);
	}
	return explosions;
}

void FullLineCombinationAnimationController::removeTetraminoOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = _tetraminoExplosionFactory->getRemoveTetraminoActionOnPositionXY(xPosition, yPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithTetraminoView);
}

void FullLineCombinationAnimationController::setCallback(std::function<void()> aCallback)
{
	FiniteTimeAction *endCallback = _tetraminoExplosionFactory->getCallbackAction(aCallback);
	_animationSynchonizer->addAnimationToQueue(endCallback);
}

