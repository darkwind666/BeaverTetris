#pragma once

#include "cocos2d.h"
#include <functional>
#include <vector>
#include "GameStructures.h"

class GameBoard;
class GameBoardViewDataSource;
class GameBoardController;

class TetraminoExplosionFactory : public cocos2d::Node
{
public:
	TetraminoExplosionFactory(GameBoardController *aGameBoardController);
	~TetraminoExplosionFactory(void);

	cocos2d::FiniteTimeAction* getTetraminosExplosionsAnimationWithPositions(std::vector<GamePositionOnBoard> aPositions);
	cocos2d::FiniteTimeAction* getRemoveTetraminoActionOnPositionXY(int xPosition, int yPosition);
	cocos2d::FiniteTimeAction* getCallbackAction(std::function<void()> aCallback);

private:

	GameBoard *_gameBoard;
	GameBoardViewDataSource *_gameBoardViewDataSource;
	GameBoardController *_gameBoardController;

	cocos2d::Node* getExplosionForOnPositionXY(int xPosition, int yPosition);
	void addExplosionsToView(std::vector<cocos2d::Node*> aExplosions);

	void setExplosionColors(cocos2d::ParticleSystem* aExplosion);
	void setExplosionParticles(cocos2d::ParticleSystem* aExplosion);
	void setExplosionPositionOnXY(cocos2d::ParticleSystem* aExplosion, int xPosition, int yPosition);

	cocos2d::FiniteTimeAction* getRemoveTetraminoAnimationOnPositionXY(int xPosition, int yPosition);
	void removeTetraminoFromBoardOnPosition(GamePositionOnBoard aPosition);
	cocos2d::Node* getTetraminoViewOnPosition(GamePositionOnBoard aPosition);
	cocos2d::FiniteTimeAction* getRemoveTetraminoAnimationWithView(cocos2d::Node *aView);

	std::vector<cocos2d::Node*> getExplosionsFromPositions(std::vector<GamePositionOnBoard> tetraminosPositions);

};

