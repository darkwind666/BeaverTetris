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
	cocos2d::FiniteTimeAction* getRemoveDetailAnimationWithDetailView(cocos2d::Node *aView);
	cocos2d::FiniteTimeAction* getRocketLaunchAnimationWithTarget(cocos2d::Node *aTarget);
	cocos2d::Vec2 getDetailViewCentrePosition(cocos2d::Node *aView);
	cocos2d::FiniteTimeAction* getDetailExplosionAnimation();
	std::vector<GamePositionOnBoard> getExplosionsPositions();
	void fillExplosionsPositionsFromLine(std::vector<GamePositionOnBoard> &explosionsPositions, int aLine);
	void fillExplosionsPositionsFromXY(std::vector<GamePositionOnBoard> &explosionsPositions, int xPosition, int yPosition);

};

