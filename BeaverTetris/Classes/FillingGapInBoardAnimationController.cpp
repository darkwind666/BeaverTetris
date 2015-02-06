#include "FillingGapInBoardAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FillingGapInBoardSystem.h"
#include "DetailViewDataSource.h"
#include "GameTimeStepController.h"
#include "FallenDetailAnimationFactory.h"

using namespace cocos2d;

FillingGapInBoardAnimationController::FillingGapInBoardAnimationController(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	FillingGapInBoardSystem *fillingGapInBoardSystem = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
	fillingGapInBoardSystem->setDelegate(this);
}


FillingGapInBoardAnimationController::~FillingGapInBoardAnimationController(void)
{
}

void FillingGapInBoardAnimationController::replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	_gameTimeStepController->setUpdateAvailable(false);

	FallenDetailAnimationFactory *fallenDetailAnimationFactory = getFallenDetailAnimationFactoryWithDetail(aDetail);

	fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	Node *follenDetail = fallenDetailAnimationFactory->getCurrentDetailView();
	FiniteTimeAction *moveDetail = fallenDetailAnimationFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);

	FiniteTimeAction *callback = CallFunc::create([this](){_gameTimeStepController->setUpdateAvailable(true);});
	this->addChild(follenDetail);
	Action *sequence = Sequence::create(actionWithDetail, callback, NULL);
	this->runAction(sequence);
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