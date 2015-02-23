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

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);

private:

	AnimationSynchonizer *_animationSynchonizer;
	TetraminoExplosionFactory *_tetraminoExplosionFactory;

	cocos2d::FiniteTimeAction* getMeteorAnimationForPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	cocos2d::Vec2 getMeteorFinalPositionFromPositions(std::vector<GamePositionOnBoard> &tetraminosPositions);
	cocos2d::Node* getMeteorWithFinalPosition(cocos2d::Vec2 aPosition);

};


