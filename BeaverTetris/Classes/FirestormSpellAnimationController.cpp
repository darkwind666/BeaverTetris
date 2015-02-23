#include "FirestormSpellAnimationController.h"
#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FirestromSpell.h"
#include "TetraminoExplosionFactory.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;
using namespace std;

FirestormSpellAnimationController::FirestormSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_tetraminoExplosionFactory, this, explosionsForRemoveCurrentDetailSpellKey);

	FirestromSpell *firestromSpellModel = (FirestromSpell*)ServiceLocator::getServiceForKey(firestormSpellModelKey);
	firestromSpellModel->setDelegate(this);
}


FirestormSpellAnimationController::~FirestormSpellAnimationController(void)
{
}

void FirestormSpellAnimationController::blowUpTetraminosForPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	FiniteTimeAction *meteorAnimation = getMeteorAnimationForPositions(tetraminosPositions);
	FiniteTimeAction *tetraminosLineExplosionAnimation = _tetraminoExplosionFactory->getTetraminosExplosionsAnimationWithPositions(tetraminosPositions);
	FiniteTimeAction *sequence = Sequence::create(meteorAnimation, tetraminosLineExplosionAnimation, NULL);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* FirestormSpellAnimationController::getMeteorAnimationForPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	Vec2 meteorFinalPosition = getMeteorFinalPositionFromPositions(tetraminosPositions);
	Node *meteor = getMeteorWithFinalPosition(meteorFinalPosition);
	float actionDuration = ccpDistance(meteorFinalPosition, meteor->getPosition()) * meteorActionDurationPerPoint;
	FiniteTimeAction *moveRocket = MoveTo::create(actionDuration, meteorFinalPosition);
	FiniteTimeAction *callback = CallFuncN::create([](Node *sender){sender->removeFromParentAndCleanup(true);});
	FiniteTimeAction *sequence = Sequence::create(moveRocket, callback, NULL);
	FiniteTimeAction *actionWithRocket = TargetedAction::create(meteor, sequence);
	return actionWithRocket;
}

Vec2 FirestormSpellAnimationController::getMeteorFinalPositionFromPositions(vector<GamePositionOnBoard> &tetraminosPositions)
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	int middleIndex = tetraminosPositions.size() / 2;
	GamePositionOnBoard middleTetraminoPosition = tetraminosPositions[middleIndex];
	Vec2 meteorFinalPosition = Vec2(middleTetraminoPosition.xPosition * tetraminoOffset.x, middleTetraminoPosition.yPosition * tetraminoOffset.y);
	return meteorFinalPosition;
}

Node* FirestormSpellAnimationController::getMeteorWithFinalPosition(Vec2 aPosition)
{
	ParticleSystem *meteor = ParticleMeteor::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(meteor, this, meteorForFirestormSpellKey);
	meteor->setPositionX(aPosition.x);
	return meteor;
}

void FirestormSpellAnimationController::removeTetraminoOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = _tetraminoExplosionFactory->getRemoveTetraminoActionOnPositionXY(xPosition, yPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithTetraminoView);
}
