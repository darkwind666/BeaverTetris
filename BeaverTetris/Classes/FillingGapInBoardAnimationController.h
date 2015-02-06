#pragma once

#include "cocos2d.h"
#include "FillingGapInBoardDelegate.h"

class GameBoardController;
class FallenDetailAnimationFactory;
class GameTimeStepController;

class FillingGapInBoardAnimationController : public cocos2d::Node, public FillingGapInBoardDelegate
{
public:
	FillingGapInBoardAnimationController(GameBoardController *aGameBoardController);
	~FillingGapInBoardAnimationController(void);

	virtual void replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	GameTimeStepController *_gameTimeStepController;

	FallenDetailAnimationFactory* getFallenDetailAnimationFactoryWithDetail(TetraminoDetail *aDetail);

};

