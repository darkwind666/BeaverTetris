#include "FallenDetailAnimationController.h"
#include "AnimationSynchonizer.h"
#include "FallenDetailAnimationFactory.h"
#include "FallenDetailAnimationDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailController.h"
#include "TetraminosFallEvent.h"
#include "FillingGapInBoardSystem.h"


using namespace cocos2d;

FallenDetailAnimationController::FallenDetailAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	FallenDetailAnimationDelegate *fallenDetailAnimationDelegate = new FallenDetailAnimationDelegate();
	_fallenDetailAnimationDelegate = fallenDetailAnimationDelegate;
	this->addChild(fallenDetailAnimationDelegate);
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
	DetailViewDataSource *currentDetailViewDataSource = _fallenDetailAnimationDelegate->getCurrentDetailViewDataSource();
	placeDetainOnNewPositionWithDataSource(aPosition, currentDetailViewDataSource);
}

void FallenDetailAnimationController::placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	DetailViewDataSource *detailViewDataSource = _fallenDetailAnimationDelegate->getDetailViewDataSource(aDetail);
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, _gameBoardController);
	FiniteTimeAction *fallenNewDetailAnimation = _fallenDetailAnimationDelegate->getAnimationWithFactoryAndPosition(fallenDetailAnimationFactory, aPosition);
	delete fallenDetailAnimationFactory;
	_animationSynchonizer->addAnimationToQueue(fallenNewDetailAnimation);
}

void FallenDetailAnimationController::replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	DetailViewDataSource *detailViewDataSource = _fallenDetailAnimationDelegate->getDetailViewDataSource(aDetail);
	placeDetainOnNewPositionWithDataSource(aPosition, detailViewDataSource);
}

void FallenDetailAnimationController::placeDetainOnNewPositionWithDataSource(GamePositionOnBoard aPosition, DetailViewDataSource *aDataSource)
{
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(aDataSource, _gameBoardController);
	fallenDetailAnimationFactory->cleanDetailViewOnBoard();
	FiniteTimeAction *actionWithDetail = _fallenDetailAnimationDelegate->getAnimationWithFactoryAndPosition(fallenDetailAnimationFactory, aPosition);
	delete fallenDetailAnimationFactory;
	_animationSynchonizer->addAnimationToQueue(actionWithDetail);
}
