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
#include "CurrentDetailExplosionFactory.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"
#include "TetraminoDetail.h"
#include "CurrentDetailDataSource.h"

using namespace cocos2d;
using namespace std;

FirestormSpellAnimationController::FirestormSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_tetraminoExplosionFactory, this, explosionsForRemoveCurrentDetailSpellKey);

	CurrentDetailExplosionFactory *currentDetailExplosionFactory = new CurrentDetailExplosionFactory(aGameBoardController);
	_currentDetailExplosionFactory = currentDetailExplosionFactory;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(currentDetailExplosionFactory, this, explosionsForRemoveCurrentDetailSpellKey); 

	_fallenDetailAnimationFactory = getDetailFactoryWithGameBoardController(aGameBoardController);

	FirestromSpell *firestromSpellModel = (FirestromSpell*)ServiceLocator::getServiceForKey(firestormSpellModelKey);
	firestromSpellModel->setDelegate(this);
}


FirestormSpellAnimationController::~FirestormSpellAnimationController(void)
{
}

FallenDetailAnimationFactory* FirestormSpellAnimationController::getDetailFactoryWithGameBoardController(GameBoardController *aGameBoardController)
{
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	function<TetraminoDetail*()> detailDataSource = [currentDetailDataSource](){
		return currentDetailDataSource->getCurrentDetail();
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	FallenDetailAnimationFactory *detailFactory = new FallenDetailAnimationFactory(detailViewDataSource, aGameBoardController);
	return detailFactory;
}

void FirestormSpellAnimationController::blowUpTetraminosAreaOnPosition(vector<GamePositionOnBoard> tetraminosPositions, GamePositionOnBoard aPosition)
{
	FiniteTimeAction *meteorAnimation = getMeteorAnimationForFinalPosition(aPosition);
	FiniteTimeAction *tetraminosLineExplosionAnimation = _tetraminoExplosionFactory->getTetraminosExplosionsAnimationWithPositions(tetraminosPositions);
	FiniteTimeAction *sequence = Sequence::create(meteorAnimation, tetraminosLineExplosionAnimation, NULL);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* FirestormSpellAnimationController::getMeteorAnimationForFinalPosition(GamePositionOnBoard aPosition)
{
	Vec2 meteorFinalPosition = getMeteorFinalPositionFromPosition(aPosition);
	Node *meteor = getMeteorWithFinalPosition(meteorFinalPosition);
	float actionDuration = ccpDistance(meteorFinalPosition, meteor->getPosition()) * meteorActionDurationPerPoint;
	FiniteTimeAction *moveRocket = MoveTo::create(actionDuration, meteorFinalPosition);
	FiniteTimeAction *callback = CallFuncN::create([](Node *sender){sender->removeFromParentAndCleanup(true);});
	FiniteTimeAction *sequence = Sequence::create(moveRocket, callback, NULL);
	FiniteTimeAction *actionWithRocket = TargetedAction::create(meteor, sequence);
	return actionWithRocket;
}

Vec2 FirestormSpellAnimationController::getMeteorFinalPositionFromPosition(GamePositionOnBoard aPosition)
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 meteorFinalPosition = Vec2(aPosition.xPosition * tetraminoOffset.x, aPosition.yPosition * tetraminoOffset.y);
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

void FirestormSpellAnimationController::removeCurrentDetailWithExplosionPosition(GamePositionOnBoard aPosition)
{
	FiniteTimeAction *meteorAnimation = getMeteorAnimationForFinalPosition(aPosition);
	FiniteTimeAction *detailExplosion = _currentDetailExplosionFactory->getCurrentDetailExplosionAnimation();
	FiniteTimeAction *removeEnimation = getCurrentDetailRemoveAnimation();
	FiniteTimeAction *sequence = Sequence::create(meteorAnimation, detailExplosion, removeEnimation, NULL);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

cocos2d::FiniteTimeAction* FirestormSpellAnimationController::getCurrentDetailRemoveAnimation()
{
	 _fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	 Node *currentDetailView = _fallenDetailAnimationFactory->getCurrentDetailView();
	 CocosNodesHelper::addChildNodeToParentNodeWithZOrderFromKey(currentDetailView, this, detailForRemoveCurrentDetailSpellKey);
	 FiniteTimeAction *callback = CallFunc::create([currentDetailView](){
	 	currentDetailView->removeFromParentAndCleanup(true);
	 });
	 return callback;
}
