#include "SimilarTetraminosAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "SimilarTetraminosCombination.h"
#include "AnimationSynchonizer.h"
#include "TetraminoExplosionFactory.h"

using namespace cocos2d;
using namespace std;

SimilarTetraminosAnimationController::SimilarTetraminosAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	SimilarTetraminosCombination *similarTetraminosCombinationModel = (SimilarTetraminosCombination*)ServiceLocator::getServiceForKey(similarTetraminosCombinationModelKey);
	similarTetraminosCombinationModel->setDelegate(this);

	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	this->addChild(_tetraminoExplosionFactory);
	_animationSynchonizer = aAnimationSynchonizer;
}


SimilarTetraminosAnimationController::~SimilarTetraminosAnimationController(void)
{
}

void SimilarTetraminosAnimationController::blowUpTetraminosForPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = getTetraminosExplosionsAnimation(tetraminosPositions);
	FiniteTimeAction *sequence = _tetraminoExplosionFactory->getTetraminosExplosionAnimationWithAction(tetraminosLineExplosionAnimation);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* SimilarTetraminosAnimationController::getTetraminosExplosionsAnimation(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create([this, tetraminosPositions](){
		vector<Node*> explosions = getExplosionsFromPositions(tetraminosPositions);
		_tetraminoExplosionFactory->addExplosionsToView(explosions);
	});
	return tetraminosLineExplosionAnimation;
}

vector<Node*> SimilarTetraminosAnimationController::getExplosionsFromPositions(vector<GamePositionOnBoard> tetraminosPositions)
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

void SimilarTetraminosAnimationController::removeTetraminoOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = _tetraminoExplosionFactory->getRemoveTetraminoActionOnPositionXY(xPosition, yPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithTetraminoView);
}

void SimilarTetraminosAnimationController::setCallback(function<void()> aCallback)
{
	FiniteTimeAction *endCallback = _tetraminoExplosionFactory->getCallbackAction(aCallback);
	_animationSynchonizer->addAnimationToQueue(endCallback);
}