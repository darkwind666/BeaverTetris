#include "RocketSpellAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "AnimationSynchonizer.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"
#include "RocketSpell.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"
#include "CurrentDetailExplosionFactory.h"

using namespace cocos2d;
using namespace std;

RocketSpellAnimationController::RocketSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;

	CurrentDetailExplosionFactory *currentDetailExplosionFactory = new CurrentDetailExplosionFactory(aGameBoardController);
	_currentDetailExplosionFactory = currentDetailExplosionFactory;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(currentDetailExplosionFactory, this, explosionsForRemoveCurrentDetailSpellKey);

	DetailViewDataSource *detailViewDataSource = getCurrentDetailViewDataSource();
	_detailViewDataSource = detailViewDataSource;
	_fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, aGameBoardController);

	RocketSpell *rocketSpellModel = (RocketSpell*)ServiceLocator::getServiceForKey(rocketSpellModelKey);
	rocketSpellModel->setDelegate(this);
}

RocketSpellAnimationController::~RocketSpellAnimationController(void)
{
}

DetailViewDataSource* RocketSpellAnimationController::getCurrentDetailViewDataSource()
{
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	function<TetraminoDetail*()> detailDataSource = [currentDetailDataSource](){
		return currentDetailDataSource->getCurrentDetail();
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	return detailViewDataSource;
}

void RocketSpellAnimationController::removeCurrentDetail()
{
	_fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	Node *currentDetailView = _fallenDetailAnimationFactory->getCurrentDetailView();
	CocosNodesHelper::addChildNodeToParentNodeWithZOrderFromKey(currentDetailView, this, detailForRemoveCurrentDetailSpellKey);
	FiniteTimeAction *removeDetailAnimation = getRemoveDetailAnimationWithDetailView(currentDetailView);
	_animationSynchonizer->addAnimationToQueue(removeDetailAnimation);
}

FiniteTimeAction* RocketSpellAnimationController::getRemoveDetailAnimationWithDetailView(Node *aView)
{
	FiniteTimeAction *rocketAnimation = getRocketLaunchAnimationWithTarget(aView);
	FiniteTimeAction *detailExplosion = _currentDetailExplosionFactory->getCurrentDetailExplosionAnimation();
	FiniteTimeAction *callback = CallFunc::create([aView](){
		aView->removeFromParentAndCleanup(true);
	});
	FiniteTimeAction *sequence = Sequence::create(rocketAnimation, detailExplosion, callback, NULL);
	return sequence;
}

FiniteTimeAction* RocketSpellAnimationController::getRocketLaunchAnimationWithTarget(Node *aTarget)
{
	ParticleSystem *rocket = ParticleMeteor::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(rocket, this, rocketForRemoveCurrentDetailSpellKey);
	Vec2 rocketFinalPosition = getDetailViewCentrePosition(aTarget);
	float actionDuration = ccpDistance(rocketFinalPosition, rocket->getPosition()) * rocketLaunchActionDurationPerPoint;
	FiniteTimeAction *moveRocket = MoveTo::create(actionDuration, rocketFinalPosition);
	FiniteTimeAction *callback = CallFuncN::create([](Node *sender){sender->removeFromParentAndCleanup(true);});
	FiniteTimeAction *sequence = Sequence::create(moveRocket, callback, NULL);
	FiniteTimeAction *actionWithRocket = TargetedAction::create(rocket, sequence);
	return actionWithRocket;
}

Vec2 RocketSpellAnimationController::getDetailViewCentrePosition(Node *aView)
{
	int tetraminosCount = _detailViewDataSource->getTetraminosCount();
	int tetraminoInMiddleIndex = tetraminosCount / 2;
	Vec2 tetraminoInMiddlePosition = _detailViewDataSource->getTetraminoPositionForIndex(tetraminoInMiddleIndex);
	Vec2 rocketFinalPositionInWorld = aView->convertToWorldSpace(tetraminoInMiddlePosition);
	Vec2 rocketFinalPosition = this->convertToNodeSpace(rocketFinalPositionInWorld);
	return rocketFinalPosition;
}