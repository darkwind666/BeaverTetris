#include "FallenDetailAnimationDelegate.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "TetrisLogicSystem.h"

using namespace cocos2d;
using namespace std;

FallenDetailAnimationDelegate::FallenDetailAnimationDelegate(void)
{
	_tetrisLogicSystem = (TetrisLogicSystem*)ServiceLocator::getServiceForKey(tetrisLogicSystemKey);
}


FallenDetailAnimationDelegate::~FallenDetailAnimationDelegate(void)
{
}

DetailViewDataSource* FallenDetailAnimationDelegate::getCurrentDetailViewDataSource()
{
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	TetraminoDetail *currentDetail = currentDetailDataSource->getCurrentDetail();
	DetailViewDataSource *currentDetailViewDataSource = getDetailViewDataSource(currentDetail);
	return currentDetailViewDataSource;
}

DetailViewDataSource* FallenDetailAnimationDelegate::getDetailViewDataSource(TetraminoDetail *aDetail)
{
	function<TetraminoDetail*()> detailDataSource = [aDetail](){
		return aDetail;
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	return detailViewDataSource;
}

FiniteTimeAction* FallenDetailAnimationDelegate::getAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition)
{
	Node *follenDetail = aFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = aFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);
	return actionWithDetail;
}

FiniteTimeAction* FallenDetailAnimationDelegate::getNewDetailAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition)
{
	_tetrisLogicSystem->setUpdatable(false);
	FiniteTimeAction *actionWithDetail = getAnimationWithFactoryAndPosition(aFactory, aPosition);
	FiniteTimeAction *callback = CallFunc::create([this](){_tetrisLogicSystem->setUpdatable(true);});
	FiniteTimeAction *sequence = Sequence::create(actionWithDetail, callback, NULL);
	FiniteTimeAction *fallenNewDetailAnimation = TargetedAction::create(this, sequence);
	return fallenNewDetailAnimation;
}