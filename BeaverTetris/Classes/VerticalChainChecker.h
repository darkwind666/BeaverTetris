#pragma once

#include <vector>
#include "GameStructures.h"

class GameBoard;
class TetraminoDetail;
class TetraminosChainCleaner;
class TetraminosCombinatorDelegate;
class ChainFromTetraminosChecker;

class VerticalChainChecker
{
public:
	VerticalChainChecker(TetraminosChainCleaner *aTetraminosChainCleaner, GameBoard *aGameBoard);
	~VerticalChainChecker(void);

	void checkChainInDetailVerticals(std::vector<GamePositionOnBoard> aTetraminos);

private:

	TetraminosChainCleaner *_tetraminosChainCleaner;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	ChainFromTetraminosChecker *_chainFromTetraminosChecker;

	std::vector<GamePositionOnBoard> getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition);

};

