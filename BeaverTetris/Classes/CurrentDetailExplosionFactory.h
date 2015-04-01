#pragma once

#include "cocos2d.h"
#include "GameStructures.h"
#include <vector>

class GameBoardController;
class TetraminoExplosionFactory;
class CurrentDetailDataSource;

class CurrentDetailExplosionFactory : public cocos2d::Node
{
public:
	CurrentDetailExplosionFactory(GameBoardController *aGameBoardController);
	~CurrentDetailExplosionFactory(void);

	cocos2d::FiniteTimeAction* getCurrentDetailExplosionAnimation();

private:

	TetraminoExplosionFactory *_tetraminoExplosionFactory;
	CurrentDetailDataSource *_currentDetailDataSource;

	std::vector<GamePositionOnBoard> getExplosionsPositions();
	void fillExplosionsPositionsFromLine(std::vector<GamePositionOnBoard> &explosionsPositions, int aLine);
	void fillExplosionsPositionsFromXY(std::vector<GamePositionOnBoard> &explosionsPositions, int xPosition, int yPosition);

};

