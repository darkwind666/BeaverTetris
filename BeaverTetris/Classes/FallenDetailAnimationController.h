#pragma once

#include "FallenDetailDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class DetailViewDataSource;
class AnimationSynchonizer;
class TetrisLogicSystem;

class FallenDetailAnimationController : public FallenDetailDelegate, public cocos2d::Node
{
public:
	FallenDetailAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~FallenDetailAnimationController(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition);
	virtual void placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);
	virtual void replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	AnimationSynchonizer *_animationSynchonizer;
	TetrisLogicSystem *_tetrisLogicSystem;

	void setUpDelegates();

	DetailViewDataSource* getCurrentDetailViewDataSource();
	DetailViewDataSource* getDetailViewDataSource(TetraminoDetail *aDetail);

	cocos2d::FiniteTimeAction* getAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition);
	cocos2d::FiniteTimeAction* getNewDetailAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition);

	void placeDetainOnNewPositionWithDataSource(GamePositionOnBoard aPosition, DetailViewDataSource *aDataSource);

};

