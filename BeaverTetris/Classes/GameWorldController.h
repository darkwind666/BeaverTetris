#pragma once

#include "cocos2d.h"

class GameBoardController;

class GameWorldController : public cocos2d::Node
{
public:
	GameWorldController(void);
	~GameWorldController(void);

private:

	GameBoardController *_gameBoardController;

	void makeControllerView();

};

