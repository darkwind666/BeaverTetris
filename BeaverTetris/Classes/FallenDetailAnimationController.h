#pragma once

#include "FallenDetailDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class DetailViewDataSource;
class AnimationSynchonizer;
class FallenDetailAnimationDelegate;

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
	FallenDetailAnimationDelegate *_fallenDetailAnimationDelegate;

	void setUpDelegates();
	void placeDetainOnNewPositionWithDataSource(GamePositionOnBoard aPosition, DetailViewDataSource *aDataSource);

};

