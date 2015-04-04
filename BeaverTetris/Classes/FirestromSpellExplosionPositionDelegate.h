#pragma once

#include "ServiceInterface.h"
#include "GameStructures.h"
#include <vector>

class GameBoard;
class CurrentDetailDataSource;

class FirestromSpellExplosionPositionDelegate
{
public:
	FirestromSpellExplosionPositionDelegate(void);
	~FirestromSpellExplosionPositionDelegate(void);

	GamePositionOnBoard getExplosionPositionFromMeteorX(int xPosition);
	bool explosionInCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition);
	std::vector<GamePositionOnBoard> getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition);


private:

	GameBoard *_gameBoard;
	CurrentDetailDataSource *_currentDetailDataSource;

	int getExplosionHeightFromExplosionX(int xPosition);
	bool checkExplosionInCurrentDetailWithXYPosition(int xPosition, int yPosition);
	bool checkExplosionInCurrentDetailWithAbsolutePosition(GamePositionOnBoard aPosition);
	bool checkExplosionInBoardWithXYPosition(int xPosition, int yPosition);
	void fillExplosionZoneRowWithPosition(std::vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition);

};

