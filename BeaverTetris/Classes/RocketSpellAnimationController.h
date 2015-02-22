#pragma once

#include "cocos2d.h"
#include "RocketSpellDelegate.h"
#include "GameStructures.h"
#include <vector>

class GameBoardController;
class AnimationSynchonizer;
class FallenDetailAnimationFactory;
class DetailViewDataSource;
class TetraminoExplosionFactory;
class CurrentDetailDataSource;

class RocketSpellAnimationController : public RocketSpellDelegate, public cocos2d::Node
{
public:
	RocketSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~RocketSpellAnimationController(void);

	virtual void removeCurrentDetail();

private:

	AnimationSynchonizer *_animationSynchonizer;
	FallenDetailAnimationFactory *_fallenDetailAnimationFactory;
	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	DetailViewDataSource *_detailViewDataSource;
	CurrentDetailDataSource *_currentDetailDataSource;

	DetailViewDataSource* getDetailViewDataSourceWithDetailData(CurrentDetailDataSource *aData);
	cocos2d::FiniteTimeAction* getDetailExplosionAnimation();
	std::vector<GamePositionOnBoard> getExplosionsPositions();

};

