#include "CurrentDetailAnimationControler.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "AnimationSynchonizer.h"
#include "CurrentDetailController.h"
#include "DetailViewDataSource.h"
#include "FallenDetailAnimationFactory.h"

using namespace cocos2d;
using namespace std;

CurrentDetailAnimationControler::CurrentDetailAnimationControler(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{

	DetailViewDataSource *currentDetailViewDataSource = getDetailViewDataSource();
	_fallenDetailAnimationFactory = new FallenDetailAnimationFactory(currentDetailViewDataSource, aGameBoardController);
	_animationSynchonizer = aAnimationSynchonizer;

	CurrentDetailController *currentDetailController = (CurrentDetailController*)ServiceLocator::getServiceForKey(currentDetailControllerKey);
	currentDetailController->setDelegate(this);
}

DetailViewDataSource* CurrentDetailAnimationControler::getDetailViewDataSource()
{
	function<TetraminoDetail*()> detailDataSource = [](){
		CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
		return currentDetailDataSource->getCurrentDetail();
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	return detailViewDataSource;
}

CurrentDetailAnimationControler::~CurrentDetailAnimationControler(void)
{
}

void CurrentDetailAnimationControler::throwCurrentDetailOnPosition(GamePositionOnBoard aPosition)
{
	_fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	Node *follenDetail = _fallenDetailAnimationFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = _fallenDetailAnimationFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);
	_animationSynchonizer->addAnimationToQueue(actionWithDetail);
}