#pragma once

#include "cocos2d.h"
#include "GameStructures.h"

class DetailViewDataSource;
class FallenDetailAnimationFactory;
class TetraminoDetail;
class TetrisLogicSystem;

class FallenDetailAnimationDelegate : public cocos2d::Node
{
public:
	FallenDetailAnimationDelegate(void);
	~FallenDetailAnimationDelegate(void);

	DetailViewDataSource* getCurrentDetailViewDataSource();
	DetailViewDataSource* getDetailViewDataSource(TetraminoDetail *aDetail);
	
	cocos2d::FiniteTimeAction* getAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition);
	cocos2d::FiniteTimeAction* getNewDetailAnimationWithFactoryAndPosition(FallenDetailAnimationFactory *aFactory, GamePositionOnBoard aPosition);

private:

	TetrisLogicSystem *_tetrisLogicSystem;

};

