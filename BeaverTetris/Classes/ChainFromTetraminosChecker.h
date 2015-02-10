#pragma once

#include <vector>
#include "GameStructures.h"

class TetraminoDetail;

class ChainFromTetraminosChecker
{
public:
	ChainFromTetraminosChecker(void);
	~ChainFromTetraminosChecker(void);

	std::vector<GamePositionOnBoard> getChainFromTetraminosPositions(std::vector<GamePositionOnBoard> aPositions, TetraminoDetail *aDetail);

private:

	void sortChains(std::vector< std::vector<GamePositionOnBoard> > &aChains);

};

