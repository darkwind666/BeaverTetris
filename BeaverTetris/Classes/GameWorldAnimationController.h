#pragma once

#include "cocos2d.h"

class GameBoardController;

class GameWorldAnimationController : public cocos2d::Node
{
public:
	GameWorldAnimationController(GameBoardController *aGameBoardController);
	~GameWorldAnimationController(void);

private:

	GameBoardController *_gameBoardController;

	void makeAnimationControllers();

};

