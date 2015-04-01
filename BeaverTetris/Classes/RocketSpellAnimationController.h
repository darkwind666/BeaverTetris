#pragma once

#include "cocos2d.h"
#include "RocketSpellDelegate.h"

class GameBoardController;
class AnimationSynchonizer;
class FallenDetailAnimationFactory;
class DetailViewDataSource;
class CurrentDetailExplosionFactory;

class RocketSpellAnimationController : public RocketSpellDelegate, public cocos2d::Node
{
public:
	RocketSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~RocketSpellAnimationController(void);

	virtual void removeCurrentDetail();

private:

	AnimationSynchonizer *_animationSynchonizer;
	FallenDetailAnimationFactory *_fallenDetailAnimationFactory;
	DetailViewDataSource *_detailViewDataSource;
	CurrentDetailExplosionFactory *_currentDetailExplosionFactory;

	DetailViewDataSource* getCurrentDetailViewDataSource();
	cocos2d::FiniteTimeAction* getRemoveDetailAnimationWithDetailView(cocos2d::Node *aView);
	cocos2d::FiniteTimeAction* getRocketLaunchAnimationWithTarget(cocos2d::Node *aTarget);
	cocos2d::Vec2 getDetailViewCentrePosition(cocos2d::Node *aView);

};

