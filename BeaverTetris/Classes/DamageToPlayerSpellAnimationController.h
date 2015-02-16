#pragma once

#include "DamageToPlayerSpellDelegate.h"
#include "cocos2d.h"
#include <vector>

class GameBoardController;
class AnimationSynchonizer;
class TetraminoExplosionFactory;

class DamageToPlayerSpellAnimationController : public cocos2d::Node, public DamageToPlayerSpellDelegate
{
public:
	DamageToPlayerSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~DamageToPlayerSpellAnimationController(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions);
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition);

private:

	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	AnimationSynchonizer *_animationSynchonizer;

	cocos2d::FiniteTimeAction* getTetraminosExplosionsAnimation(std::vector<GamePositionOnBoard> tetraminosPositions);
	std::vector<cocos2d::Node*> getExplosionsFromPositions(std::vector<GamePositionOnBoard> tetraminosPositions);

};

