#pragma once

#include "CurrentDetailControllerDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class DetailViewDataSource;
class GameTimeStepController;

class CurrentDetailAnimationControler : public cocos2d::Node, public CurrentDetailControllerDelegate
{
public:
	CurrentDetailAnimationControler(GameBoardController *aGameBoardController);
	~CurrentDetailAnimationControler(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition);

private:

	FallenDetailAnimationFactory *_fallenDetailAnimationFactory;
	GameTimeStepController *_gameTimeStepController;

	DetailViewDataSource* getDetailViewDataSource();

};

