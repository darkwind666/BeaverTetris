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

using namespace cocos2d;
using namespace std;

RocketSpellAnimationController::RocketSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_detailViewDataSource = getDetailViewDataSourceWithDetailData(_currentDetailDataSource);
	_tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	this->addChild(_tetraminoExplosionFactory,1);

	_fallenDetailAnimationFactory = new FallenDetailAnimationFactory(_detailViewDataSource, aGameBoardController);
	_animationSynchonizer = aAnimationSynchonizer;

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
	this->addChild(currentDetailView);
	ParticleSystem *rocket = ParticleMeteor::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(rocket, this, rocketForRemoveCurrentDetailSpellKey);

	int tetraminosCount = _detailViewDataSource->getTetraminosCount();
	int tetraminoInMiddleIndex = tetraminosCount / 2;
	Vec2 tetraminoInMiddlePosition = _detailViewDataSource->getTetraminoPositionForIndex(tetraminoInMiddleIndex);
	Vec2 rocketFinalPositionInWorld = currentDetailView->convertToWorldSpace(tetraminoInMiddlePosition);
	Vec2 rocketFinalPosition = this->convertToNodeSpace(rocketFinalPositionInWorld);


	float actionDuration = ccpDistance(currentDetailView->getPosition(), rocket->getPosition()) * rocketLaunchActionDurationPerPoint;
	FiniteTimeAction *moveRocket = MoveTo::create(actionDuration, rocketFinalPosition);
	FiniteTimeAction *detailExplosion = getDetailExplosionAnimation();
	FiniteTimeAction *callback = CallFuncN::create([this, currentDetailView](Node *sender){
		sender->removeFromParentAndCleanup(true);
		currentDetailView->removeFromParentAndCleanup(true);
	});

	FiniteTimeAction *sequence = Sequence::create(moveRocket, detailExplosion, callback, NULL);
	FiniteTimeAction *rocketAnimation = TargetedAction::create(rocket, sequence);
	_animationSynchonizer->addAnimationToQueue(rocketAnimation);
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
	int detailWidth = currentDetail->getDetailWidth();

	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{

		for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
		{

			Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(widthIndex, heightIndex);
			if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
			{
				GamePositionOnBoard positionInDetail;
				positionInDetail.xPosition = widthIndex;
				positionInDetail.yPosition = heightIndex;
				GamePositionOnBoard absolutePosition = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
				explosionsPositions.push_back(absolutePosition);
			}

		}

	}
	return explosionsPositions;
}