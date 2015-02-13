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

	std::vector< std::vector<int> > getBoardTetraminosTemplate();
    std::vector< std::vector<int> > convertMasiveToVector(int *aSourceMassive);
	std::vector<int> getTetraminosElementsLineFromSource(int yIndex, int *aSourceMassive);
	void fillBoardWithTetraminos(std::vector< std::vector<int> > aTetraminoElements);
	void fillBoardLineWithTetraminos(int aLineIndex, std::vector<int> aTetraminoElements);

};

