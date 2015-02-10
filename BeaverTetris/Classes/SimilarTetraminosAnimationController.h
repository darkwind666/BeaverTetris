#pragma once

#include "SimilarTetraminosCombinationDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminoExplosionFactory;

class SimilarTetraminosAnimationController : public cocos2d::Node, public SimilarTetraminosCombinationDelegate 
{
public:
	SimilarTetraminosAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~SimilarTetraminosAnimationController(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);
	virtual void setCallback(std::function<void()> aCallback);

private:

	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	AnimationSynchonizer *_animationSynchonizer;

	cocos2d::FiniteTimeAction* getTetraminosExplosionsAnimation(std::vector<GamePositionOnBoard> tetraminosPositions);
	std::vector<cocos2d::Node*> getExplosionsFromPositions(std::vector<GamePositionOnBoard> tetraminosPositions);

};

