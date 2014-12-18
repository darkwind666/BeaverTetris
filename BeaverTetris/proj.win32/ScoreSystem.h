#pragma once

#include "GameSystemInterface.h"
#include <vector>
#include "AwardForTetraminoDataSource.h"
#include "GameBoard.h"
#include "CurrentPlayerDataSource.h"
#include "DetailsFromBoardDataSource.h"
#include "TetraminosCombinatorDelegate.h"

#include "FullLineCombination.h"

class ScoreSystem :public GameSystemInterface
{
public:
	ScoreSystem(AwardForTetraminoDataSource *aAwardForTetraminoDataSource, GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~ScoreSystem(void);

	void updateSystem(float deltaTime);

private:


	FullLineCombination *_fullLineCombination;


	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	GameBoard *_gameBoard;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;

	
	void checkTetraminoChains();
	bool checkChainInDetail(TetraminoDetail *aDetail);
	bool checkChainInDetailHorisontals(TetraminoDetail *aDetail);
	bool checkChainInDetailVerticals(TetraminoDetail *aDetail);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);

	void checkFilledLines();
	bool fullLineCheck(int lineIndex);
	int getAwardForTetramino(Tetramino *aTetramino);
	void removeKilledTetraminos(int lineIndex);

};

