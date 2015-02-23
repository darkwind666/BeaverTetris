#pragma once

#include "cocos2d.h"
#include "FirestormSpellDelegate.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminoExplosionFactory;

class FirestormSpellAnimationController : public cocos2d::Node, public FirestormSpellDelegate
{
public:
	FirestormSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~FirestormSpellAnimationController(void);

	virtual void blowUpTetraminosAreaOnPosition(std::vector<GamePositionOnBoard> tetraminosPositions, GamePositionOnBoard aPosition);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);

private:

	AnimationSynchonizer *_animationSynchonizer;
	TetraminoExplosionFactory *_tetraminoExplosionFactory;

	cocos2d::FiniteTimeAction* getMeteorAnimationForFinalPosition(GamePositionOnBoard aPosition);
	cocos2d::Vec2 getMeteorFinalPositionFromPosition(GamePositionOnBoard aPosition);
	cocos2d::Node* getMeteorWithFinalPosition(cocos2d::Vec2 aPosition);

};


