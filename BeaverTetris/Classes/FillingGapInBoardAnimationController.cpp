#include "FillingGapInBoardAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FillingGapInBoardSystem.h"
#include "DetailViewDataSource.h"
#include "AnimationSynchonizer.h"
#include "FallenDetailAnimationFactory.h"

using namespace cocos2d;

FillingGapInBoardAnimationController::FillingGapInBoardAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_gameBoardController = aGameBoardController;
	_animationSynchonizer = aAnimationSynchonizer;
	FillingGapInBoardSystem *fillingGapInBoardSystem = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
	fillingGapInBoardSystem->setDelegate(this);
}


FillingGapInBoardAnimationController::~FillingGapInBoardAnimationController(void)
{
}

void FillingGapInBoardAnimationController::replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = getFallenDetailAnimationFactoryWithDetail(aDetail);

	fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	Node *follenDetail = fallenDetailAnimationFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = fallenDetailAnimationFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);
	_animationSynchonizer->addAnimationToQueue(actionWithDetail);
	
	delete fallenDetailAnimationFactory;
}

FallenDetailAnimationFactory* FillingGapInBoardAnimationController::getFallenDetailAnimationFactoryWithDetail(TetraminoDetail *aDetail)
{
	function<TetraminoDetail*()> detailDataSource = [aDetail](){
		return aDetail;
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, _gameBoardController);
	return fallenDetailAnimationFactory;
}