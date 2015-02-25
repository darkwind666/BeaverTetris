#include "TetraminosFallEventAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "TetraminosFallEvent.h"
#include "DetailViewDataSource.h"
#include "AnimationSynchonizer.h"
#include "FallenDetailAnimationFactory.h"
#include "TetrisLogicSystem.h"

using namespace cocos2d;

TetraminosFallEventAnimationController::TetraminosFallEventAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_gameBoardController = aGameBoardController;
	_animationSynchonizer = aAnimationSynchonizer;
	_tetrisLogicSystem = (TetrisLogicSystem*)ServiceLocator::getServiceForKey(tetrisLogicSystemKey);
	TetraminosFallEvent *tetraminosFallEventModel = (TetraminosFallEvent*)ServiceLocator::getServiceForKey(tetraminosFallEventModelKey);
	tetraminosFallEventModel->setDelegate(this);
}


TetraminosFallEventAnimationController::~TetraminosFallEventAnimationController(void)
{
}

void TetraminosFallEventAnimationController::placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	_tetrisLogicSystem->setUpdatable(false);
	FiniteTimeAction *actionWithDetail = getFallenDetailAnimationWithPosition(aDetail, aPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithDetail);
}

FallenDetailAnimationFactory* TetraminosFallEventAnimationController::getFallenDetailAnimationFactoryWithDetail(TetraminoDetail *aDetail)
{
	function<TetraminoDetail*()> detailDataSource = [aDetail](){
		return aDetail;
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = new FallenDetailAnimationFactory(detailViewDataSource, _gameBoardController);
	return fallenDetailAnimationFactory;
}

FiniteTimeAction* TetraminosFallEventAnimationController::getFallenDetailAnimationWithPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	FallenDetailAnimationFactory *fallenDetailAnimationFactory = getFallenDetailAnimationFactoryWithDetail(aDetail);
	Node *follenDetail = fallenDetailAnimationFactory->getCurrentDetailView();
	this->addChild(follenDetail);
	FiniteTimeAction *moveDetail = fallenDetailAnimationFactory->getDetailAnimationWithFinalPosition(aPosition);
	FiniteTimeAction *callback = CallFunc::create([this](){_tetrisLogicSystem->setUpdatable(true);});
	FiniteTimeAction *sequence = Sequence::create(moveDetail, callback, NULL);
	FiniteTimeAction *actionWithDetail = TargetedAction::create(follenDetail, sequence);
	delete fallenDetailAnimationFactory;
	return actionWithDetail;
}