#pragma once

#include "TetraminosFallEventDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class AnimationSynchonizer;
class TetrisLogicSystem;

class TetraminosFallEventAnimationController : public TetraminosFallEventDelegate, public cocos2d::Node
{
public:
	TetraminosFallEventAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~TetraminosFallEventAnimationController(void);

	virtual void placeNewDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	AnimationSynchonizer *_animationSynchonizer;
	TetrisLogicSystem *_tetrisLogicSystem;
	
	FallenDetailAnimationFactory* getFallenDetailAnimationFactoryWithDetail(TetraminoDetail *aDetail);
	cocos2d::FiniteTimeAction* getFallenDetailAnimationWithPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);
};

