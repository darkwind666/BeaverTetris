#pragma once

#include "GameBoard.h"
#include "ActiveDetails.h"
#include <vector>
#include "DetailsFromBoardDataSource.h"

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

	std::vector < std::vector <GamePositionOnBoard> > getTetraminoDetailsInGame();
	void replaceTetraminosDetailsFromBoardToActiveDetailsStrore(std::vector < std::vector <GamePositionOnBoard> > aTetraminoDetailsInGame);

	GamePositionOnBoard  getMaxDetailPositionFromDetailsElements(std::vector <GamePositionOnBoard> aDetailElements);
	GamePositionOnBoard  getMinDetailPositionFromDetailsElements(std::vector <GamePositionOnBoard> aDetailElements);
	GamePositionOnBoard getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition);

	TetraminoDetail* getDetailWithMaxMinDetailPositionAndDetailSize(std::vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition, GamePositionOnBoard aDetailSize);

};

