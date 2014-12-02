#pragma once

#include "GameBoard.h"
#include "ActiveDetails.h"
#include <vector>
#include "DetailsFromBoardDataSource.h"
#include "TetraminosCombinatorDelegate.h"

class TetraminosSeparatorDelegate
{
public:
	TetraminosSeparatorDelegate(GameBoard *aGameBoard, ActiveDetails *aActiveDetails);
	~TetraminosSeparatorDelegate(void);

	void separateTetraminos();

private:

	GameBoard *_gameBoard;
	ActiveDetails *_activeDetails;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;

	std::vector < std::vector <GamePositionOnBoard> > getTetraminoDetailsInGame();
	void replaceTetraminosDetailsFromBoardToActiveDetailsStrore(std::vector < std::vector <GamePositionOnBoard> > aTetraminoDetailsInGame);

};

