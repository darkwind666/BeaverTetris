#pragma once

#include "cocos2d.h"

class GameBoardController;
class GameTimeStepController;
class GameWorldAnimationController;

class GameWorldController : public cocos2d::Node
{
public:
	GameWorldController(void);
	~GameWorldController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);

	void startGame();
	void pauseGameWorld();
	void resumeGameWorld();

private:

	GameBoardController *_gameBoardController;
	GameTimeStepController *_gameTimeStepController;
	GameWorldAnimationController *_gameWorldAnimationController;
	cocos2d::Node* _backgroundController;
	bool _gameStarted;

	void makeControllerView();

};

