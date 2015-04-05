#pragma once

#include "cocos2d.h"
#include "FirestormSpellDelegate.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminoExplosionFactory;
class CurrentDetailExplosionFactory;
class FallenDetailAnimationFactory;

class FirestormSpellAnimationController : public cocos2d::Node, public FirestormSpellDelegate
{
public:
	FirestormSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~FirestormSpellAnimationController(void);

	virtual void throwFireballs(std::vector<FireballInformation> aFireballs);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);
	virtual void removeCurrentDetailWithExplosionPosition(GamePositionOnBoard aPosition);

private:

	AnimationSynchonizer *_animationSynchonizer;
	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	CurrentDetailExplosionFactory *_currentDetailExplosionFactory;
	FallenDetailAnimationFactory *_fallenDetailAnimationFactory;

	FallenDetailAnimationFactory* getDetailFactoryWithGameBoardController(GameBoardController *aGameBoardController);
	cocos2d::FiniteTimeAction* getMeteorsAnimationForFireballs(std::vector<FireballInformation> aFireballs);
	cocos2d::FiniteTimeAction* getMeteorAnimationForFinalPositionAndIndex(GamePositionOnBoard aPosition, int aIndex);
	cocos2d::Vec2 getMeteorFinalPositionFromPosition(GamePositionOnBoard aPosition);
	cocos2d::Node* getMeteorWithFinalPosition(cocos2d::Vec2 aPosition);
	cocos2d::FiniteTimeAction* getCurrentDetailRemoveAnimation();

};


