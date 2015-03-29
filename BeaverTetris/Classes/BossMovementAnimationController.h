#pragma once

#include "cocos2d.h"
#include "BossMovementDelegate.h"
#include <functional>

class GameBoardController;
class AnimationSynchonizer;
class GameBoard;
class GameBoardViewDataSource;

class BossMovementAnimationController : public BossMovementDelegate, public cocos2d::Node
{
public:
	BossMovementAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~BossMovementAnimationController(void);

	virtual void moveBossFromStartPositionToFinal(GamePositionOnBoard aStartPosition, GamePositionOnBoard aFinalPosition);

private:

	GameBoardController *_gameBoardController;
	AnimationSynchonizer *_animationSynchonizer;
	GameBoard *_gameBoard;
	GameBoardViewDataSource *_gameBoardViewDataSource;

	cocos2d::Node* getBossViewWithStartPosition(GamePositionOnBoard aStartPosition);
	cocos2d::FiniteTimeAction* getAnimationWithBossViewAndFinalPosition(cocos2d::Node *aView, GamePositionOnBoard aFinalPosition);
	cocos2d::FiniteTimeAction* getMoveBossAnimationWithViewAndFinalPosition(cocos2d::Node *aView, GamePositionOnBoard aFinalPosition);
	std::function<void(Node*)> getAnimationEndCallbackWithFinalPosition(GamePositionOnBoard aFinalPosition);
};

