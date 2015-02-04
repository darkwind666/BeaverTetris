#pragma once

#include "cocos2d.h"
#include "FullLineCombinationDelegate.h"
#include "GameStructures.h"
#include <vector>

class GameBoardViewDataSource;
class GameBoardController;
class GameBoard;
class TetraminoColorsDataSource;

class FullLineCombinationAnimationController : public cocos2d::Node, public FullLineCombinationDelegate
{
public:
	FullLineCombinationAnimationController(GameBoardController *aGameBoardController);
	~FullLineCombinationAnimationController(void);

	virtual void blowUpLine(int aLineIndex);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);
	virtual void setCallback(std::function<void()> aCallback);

private:

	GameBoardController *_gameBoardController;
	GameBoardViewDataSource *_gameBoardViewDataSource;
	GameBoard *_gameBoard;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;
	cocos2d::FiniteTimeAction *_sequence;

	cocos2d::FiniteTimeAction* getTetraminosLineExplosionAnimation(int aLineIndex);
	std::vector<cocos2d::Node*> getExplosionsInLine(int aLineIndex);
	cocos2d::Node* getExplosionForOnPositionXY(int xPosition, int yPosition);
	void setExplosionColors(cocos2d::ParticleSystem* aExplosion);
	void setExplosionParticles(cocos2d::ParticleSystem* aExplosion);
	void setExplosionPositionOnXY(cocos2d::ParticleSystem* aExplosion, int xPosition, int yPosition);
	void addExplosionsToView(std::vector<cocos2d::Node*> aExplosions);

	cocos2d::FiniteTimeAction* getRemoveTetraminoAnimationOnPositionXY(int xPosition, int yPosition);
	void removeTetraminoFromBoardOnPosition(GamePositionOnBoard aPosition);
	cocos2d::Node* getTetraminoViewOnPosition(GamePositionOnBoard aPosition);
	cocos2d::FiniteTimeAction* getRemoveTetraminoAnimationWithView(cocos2d::Node *aView);
};

