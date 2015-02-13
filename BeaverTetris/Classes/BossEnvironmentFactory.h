#pragma once

#include <vector>
#include "GameEnums.h"

class GameBoard;

class BossEnvironmentFactory
{
public:
	BossEnvironmentFactory(void);
	~BossEnvironmentFactory(void);

	void makeBossEnvironment();

private:

	GameBoard *_gameBoard;

	void makeLineForIndex(int aLineIndex);
	std::vector<TetraminoType> getTetraminoTypesInLine(int aLineIndex);
	void cleanFullLineInTetraminosTypes(std::vector<TetraminoType> &aTetraminosInLine);
	void cleanTetraminosChainsInTetraminosTypes(std::vector<TetraminoType> &aTetraminosInLine);
	void writeTetraminosInBoardLine(std::vector<TetraminoType> aTetraminosInLine, int aLineIndex);

};

