#pragma once

#include "GameBoard.h"
#include "TetraminoDetail.h"
#include "CurrentPlayerDataSource.h"
#include "AwardForTetraminoDataSource.h"
#include "TetraminosCombinatorDelegate.h"
#include "DetailsFromBoardDataSource.h"

class SimilarTetraminosCombination
{
public:
	SimilarTetraminosCombination(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~SimilarTetraminosCombination(void);

	void checkSimilarTetraminosCombination();

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;

	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;

	bool checkChainInDetail(TetraminoDetail *aDetail);
	bool checkChainInDetailHorisontals(TetraminoDetail *aDetail);
	bool checkChainInDetailVerticals(TetraminoDetail *aDetail);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);

};

