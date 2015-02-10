#pragma once

#include <vector>
#include "ServiceInterface.h"
#include "GameStructures.h"

class GameBoard;
class DetailsFromBoardDataSource;
class SimilarTetraminosCombinationDelegate;
class TetraminosChainCleaner;
class ChainFromTetraminosChecker;
class HorisontalChainChecker;
class VerticalChainChecker;

class SimilarTetraminosCombination : public ServiceInterface
{
public:
	SimilarTetraminosCombination(GameBoard *aGameBoard);
	~SimilarTetraminosCombination(void);

	void checkSimilarTetraminosCombination();
	void setDelegate(SimilarTetraminosCombinationDelegate *aDelegate);

private:

	TetraminosChainCleaner *_tetraminosChainCleaner;
	ChainFromTetraminosChecker *_chainFromTetraminosChecker;
	HorisontalChainChecker *_horisontalChainChecker;
	VerticalChainChecker *_verticalChainChecker;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;

	void checkChainInDetailElements(std::vector<GamePositionOnBoard> aTetraminos);

};

