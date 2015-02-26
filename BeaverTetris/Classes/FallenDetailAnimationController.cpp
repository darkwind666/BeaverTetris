#include "FallenDetailAnimationController.h"
#include "AnimationSynchonizer.h"
#include "GameBoardController.h"
#include "FallenDetailAnimationFactory.h"
#include "DetailViewDataSource.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "TetrisLogicSystem.h"
#include "CurrentDetailController.h"
#include "TetraminosFallEvent.h"
#include "FillingGapInBoardSystem.h"

using namespace cocos2d;
using namespace std;

FallenDetailAnimationController::FallenDetailAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	_tetrisLogicSystem = (TetrisLogicSystem*)ServiceLocator::getServiceForKey(tetrisLogicSystemKey);
	setUpDelegates();
}


FallenDetailAnimationController::~FallenDetailAnimationController(void)
{
}

void FallenDetailAnimationController::setUpDelegates()
{
	FillingGapInBoardSystem *fillingGapInBoardSystem = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
	fillingGapInBoardSystem->setDelegate(this);

	CurrentDetailController *currentDetailController = (CurrentDetailController*)ServiceLocator::getServiceForKey(currentDetailControllerKey);
	currentDetailController->setDelegate(this);

	TetraminosFallEvent *tetraminosFallEvent = (TetraminosFallEvent*)ServiceLocator::getServiceForKey(tetraminosFallEventModelKey);
	tetraminosFallEvent->setDelegate(this);
}

void FallenDetailAnimationController::throwCurrentDetailOnPosition(GamePositionOnBoard aPosition)
{
	DetailViewDataSource *currentDetailViewDataSource = getCurrentDetailViewDataSource();
	placeDetainOnNewPositionWithDataSource(aPosition, currentDetailViewDataSource);
}

void FallenDetailAnimationController::placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	_tetrisLogicSystem->setUpdatable(false);
	DetailViewDataSource *detailViewDataSource = getDetailViewDataSource(aDetail);
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, _gameBoardController);
	FiniteTimeAction *fallenNewDetailAnimation = getNewDetailAnimationWithFactoryAndPosition(fallenDetailAnimationFactory, aPosition);
	delete fallenDetailAnimationFactory;
	_animationSynchonizer->addAnimationToQueue(fallenNewDetailAnimation);
}

void FallenDetailAnimationController::replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	DetailViewDataSource *detailViewDataSource = getDetailViewDataSource(aDetail);
	placeDetainOnNewPositionWithDataSource(aPosition, detailViewDataSource);
}






void FallenDetailAnimationController::placeDetainOnNewPositionWithDataSource(GamePositionOnBoard aPosition, DetailViewDataSource *aDataSource)
{
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(aDataSource, _gameBoardController);
	fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	FiniteTimeAction *actionWithDetail = getAnimationWithFactoryAndPosition(fallenDetailAnimationFactory, aPosition);
	delete fallenDetailAnimationFactory;
	_animationSynchonizer->addAnimationToQueue(actionWithDetail);
}

DetailViewDataSource* FallenDetailAnimationController::getCurrentDetailViewDataSource()
{
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	TetraminoDetail *currentDetail = currentDetailDataSource->getCurrentDetail();
	DetailViewDataSource *currentDetailViewDataSource = getDetailViewDataSource(currentDetail);
	return currentDetailViewDataSource;
}

DetailViewDataSource* FallenDetailAnimationController::getDetailViewDataSource(TetraminoDetail *aDetail)
{
	function<TetraminoDetail*()> detailDataSource = [aDetail](){
		return aDetail;
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	return detailViewDataSource;
}

FiniteTimeAction* FallenDetailAnimationController::getAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition)
{
	Node *follenDetail = aFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = aFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, moveDetail);
	return actionWithDetail;
}

FiniteTimeAction* FallenDetailAnimationController::getNewDetailAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition)
{
	FiniteTimeAction *actionWithDetail = getAnimationWithFactoryAndPosition(aFactory, aPosition);
	FiniteTimeAction *callback = CallFunc::create([this](){_tetrisLogicSystem->setUpdatable(true);});
	FiniteTimeAction *sequence = Sequence::create(actionWithDetail, callback, NULL);
	FiniteTimeAction *fallenNewDetailAnimation = TargetedAction::create(this, sequence);
	return fallenNewDetailAnimation;
}