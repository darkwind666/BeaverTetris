#pragma once

#include "CurrentDetailControllerDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class DetailViewDataSource;
class AnimationSynchonizer;

class CurrentDetailAnimationControler : public cocos2d::Node, public CurrentDetailControllerDelegate
{
public:
	CurrentDetailAnimationControler(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~CurrentDetailAnimationControler(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition);

private:

	FallenDetailAnimationFactory *_fallenDetailAnimationFactory;
	AnimationSynchonizer *_animationSynchonizer;

	DetailViewDataSource* getDetailViewDataSource();

};

