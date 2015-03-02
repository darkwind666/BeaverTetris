#pragma once

#include "cocos2d.h"
#include "CohesionSpellDelegate.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminosAppearanceAnimationFactory;

class CohesionSpellAnimationController : public CohesionSpellDelegate, public cocos2d::Node
{
public:
	CohesionSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~CohesionSpellAnimationController(void);

	virtual void makeTetraminoOnPosition(GamePositionOnBoard aPosition);

private:

	AnimationSynchonizer *_animationSynchonizer;
	TetraminosAppearanceAnimationFactory *_tetraminosAppearanceAnimationFactory;
};

