#include "FallenDetailAnimationDelegate.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "GameViewStyleHelper.h"
#include "GameSoundsKeys.h"

using namespace cocos2d;
using namespace std;

FallenDetailAnimationDelegate::FallenDetailAnimationDelegate(void)
{
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
	FiniteTimeAction *moveDetail = getReplaceDetailAnimationWithFactoryAndPosition(aFactory, aPosition);
	FiniteTimeAction *soundAction = GameViewStyleHelper::getSoundActionWithKey(detailFallingSoundKey);
	FiniteTimeAction *sequence = Sequence::create(moveDetail, soundAction, NULL);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(moveDetail->getTarget(), sequence);
	return actionWithDetail;
}

FiniteTimeAction* FallenDetailAnimationDelegate::getReplaceDetailAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition)
{
	Node *follenDetail = aFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = aFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);
	return actionWithDetail;
}

