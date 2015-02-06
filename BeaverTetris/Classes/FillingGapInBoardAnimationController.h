#pragma once

#include "cocos2d.h"
#include "FillingGapInBoardDelegate.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class AnimationSynchonizer;

class FillingGapInBoardAnimationController : public cocos2d::Node, public FillingGapInBoardDelegate
{
public:
	FillingGapInBoardAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~FillingGapInBoardAnimationController(void);

	virtual void replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	AnimationSynchonizer *_animationSynchonizer;

	FallenDetailAnimationFactory* getFallenDetailAnimationFactoryWithDetail(TetraminoDetail *aDetail);

};

