#pragma once

#include "cocos2d.h"

class GameBoardController;

class GameWorldController : public cocos2d::Node
{
public:
	GameWorldController(void);
	~GameWorldController(void);

	virtual void update(float delta);

private:

	GameBoardController *_gameBoardController;

	void makeControllerView();

};

