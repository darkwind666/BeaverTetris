#include "RocketSpellAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "AnimationSynchonizer.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"
#include "FallenDetailAnimationFactory.h"
#include "RocketSpell.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"
#include "TetraminoExplosionFactory.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;
using namespace std;

RocketSpellAnimationController::RocketSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_currentDetailDataSource = currentDetailDataSource;

	DetailViewDataSource *detailViewDataSource = getDetailViewDataSourceWithDetailData(currentDetailDataSource);
	_detailViewDataSource = detailViewDataSource;
	_fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, aGameBoardController);

	TetraminoExplosionFactory *tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	_tetraminoExplosionFactory = tetraminoExplosionFactory;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(tetraminoExplosionFactory, this, explosionsForRemoveCurrentDetailSpellKey);

	RocketSpell *rocketSpellModel = (RocketSpell*)ServiceLocator::getServiceForKey(rocketSpellModelKey);
	rocketSpellModel->setDelegate(this);
}

RocketSpellAnimationController::~RocketSpellAnimationController(void)
{
}

DetailViewDataSource* RocketSpellAnimationController::getDetailViewDataSourceWithDetailData(CurrentDetailDataSource *aData)
{
	function<TetraminoDetail*()> detailDataSource = [aData](){
		return aData->getCurrentDetail();
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
	FiniteTimeAction *detailExplosion = getDetailExplosionAnimation();
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
	FiniteTimeAction *callback = CallFuncN::create([this](Node *sender){sender->removeFromParentAndCleanup(true);});
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

FiniteTimeAction* RocketSpellAnimationController::getDetailExplosionAnimation()
{
	vector<GamePositionOnBoard> explosionsPositions = getExplosionsPositions();
	FiniteTimeAction *explosions = _tetraminoExplosionFactory->getTetraminosExplosionsAnimationWithPositions(explosionsPositions);
	return explosions;
}

vector<GamePositionOnBoard> RocketSpellAnimationController::getExplosionsPositions()
{
	vector<GamePositionOnBoard> explosionsPositions;
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailHeight = currentDetail->getDetailHeight();
	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{
		fillExplosionsPositionsFromLine(explosionsPositions, heightIndex);
	}
	return explosionsPositions;
}

void RocketSpellAnimationController::fillExplosionsPositionsFromLine(vector<GamePositionOnBoard> &explosionsPositions, int aLine)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailWidth = currentDetail->getDetailWidth();
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(widthIndex, aLine);
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			fillExplosionsPositionsFromXY(explosionsPositions, widthIndex, aLine);
		}
	}
}

void RocketSpellAnimationController::fillExplosionsPositionsFromXY(vector<GamePositionOnBoard> &explosionsPositions, int xPosition, int yPosition)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard positionInDetail;
	positionInDetail.xPosition = xPosition;
	positionInDetail.yPosition = yPosition;
	GamePositionOnBoard absolutePosition = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
	explosionsPositions.push_back(absolutePosition);
}