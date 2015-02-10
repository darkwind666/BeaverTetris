#pragma once

#include <vector>
#include "GameStructures.h"

class GameBoard;
class TetraminoDetail;
class TetraminosChainCleaner;
class TetraminosCombinatorDelegate;
class ChainFromTetraminosChecker;

class HorisontalChainChecker
{
public:
	HorisontalChainChecker(TetraminosChainCleaner *aTetraminosChainCleaner, GameBoard *aGameBoard);
	~HorisontalChainChecker(void);

	void checkChainInDetailHorisontals(std::vector<GamePositionOnBoard> aTetraminos);

private:

	TetraminosChainCleaner *_tetraminosChainCleaner;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	ChainFromTetraminosChecker *_chainFromTetraminosChecker;

	std::vector<GamePositionOnBoard> getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition);

};

