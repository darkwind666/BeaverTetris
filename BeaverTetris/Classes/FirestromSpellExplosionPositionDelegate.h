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
	void cleanFirestorm();

private:

	GameBoard *_gameBoard;
	CurrentDetailDataSource *_currentDetailDataSource;
	std::vector< std::vector<int> > _tetraminosLives;
	bool _currentDetailExplosion;

	std::vector< std::vector<int> > getTetraminosLives();
	void fillTetraminosLives(std::vector< std::vector<int> > &tetraminosLives);


	int getExplosionHeightFromExplosionX(int xPosition);
	void reduceTetraminosLivesOnExplosionOnXYPosition(int xPosition, int yPosition);
	bool checkExplosionInCurrentDetailWithXYPosition(int xPosition, int yPosition);
	bool checkExplosionInCurrentDetailWithAbsolutePosition(GamePositionOnBoard aPosition);
	bool checkExplosionInBoardWithXYPosition(int xPosition, int yPosition);
	void fillExplosionZoneRowWithPosition(std::vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition);

};

