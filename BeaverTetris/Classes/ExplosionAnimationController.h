#pragma once

#include <vector>
#include <functional>
#include "GameStructures.h"
#include "cocos2d.h"
#include "ExplosionAnimationDelegate.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminoExplosionFactory;
class GameBoard;

class ExplosionAnimationController : public cocos2d::Node, public ExplosionAnimationDelegate
{
public:
	ExplosionAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~ExplosionAnimationController(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	virtual void blowUpLine(int aLineIndex);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);
	virtual void setCallback(std::function<void()> aCallback);

private:

	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	AnimationSynchonizer *_animationSynchonizer;
	GameBoard *_gameBoard;

	void setUpDelegates();
	cocos2d::FiniteTimeAction* getTetraminosExplosionsAnimation(std::vector<GamePositionOnBoard> tetraminosPositions);
	std::vector<cocos2d::Node*> getExplosionsFromPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	std::vector<GamePositionOnBoard> getTetraminosPositionsInLine(int aLineIndex);

};

