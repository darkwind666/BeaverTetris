#pragma once

#include "cocos2d.h"

class GameBoardController;
class AnimationSynchonizer;

class GameWorldAnimationController : public cocos2d::Node
{
public:
	GameWorldAnimationController(GameBoardController *aGameBoardController);
	~GameWorldAnimationController(void);

	void updateAnimation();

private:

	GameBoardController *_gameBoardController;
	AnimationSynchonizer *_animationSynchonizer;

	void makeAnimationControllers();

};

