#pragma once

#include "cocos2d.h"
#include "FullLineCombinationDelegate.h"
#include "GameStructures.h"
#include <vector>

class GameBoardController;
class GameBoard;
class AnimationSynchonizer;
class TetraminoExplosionFactory;

class FullLineCombinationAnimationController : public cocos2d::Node, public FullLineCombinationDelegate
{
public:
	FullLineCombinationAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~FullLineCombinationAnimationController(void);

	virtual void blowUpLine(int aLineIndex);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);
	virtual void setCallback(std::function<void()> aCallback);

private:

	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	AnimationSynchonizer *_animationSynchonizer;
	GameBoard *_gameBoard;

	cocos2d::FiniteTimeAction* getTetraminosLineExplosionAnimation(int aLineIndex);
	std::vector<cocos2d::Node*> getExplosionsInLine(int aLineIndex);
};

