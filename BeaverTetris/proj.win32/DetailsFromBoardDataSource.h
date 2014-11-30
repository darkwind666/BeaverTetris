#pragma once

#include <vector>
#include "GameStructures.h"
#include "GameBoard.h"

class DetailsFromBoardDataSource
{
public:
	DetailsFromBoardDataSource(GameBoard *aGameBoard);
	~DetailsFromBoardDataSource(void);

	std::vector < std::vector <GamePositionOnBoard> > getTetraminoDetailsInGame();

private:

	GameBoard *_gameBoard;

	std::vector <GamePositionOnBoard> getDetailFromStartPosition(int xPosition, int yPosition);
	void setDetailsInExtractedDetailsData(std::vector <GamePositionOnBoard> aDetailElements, GameBoard *aExtractedDetailsData);
	void fillTetraminoChainWithPositionXY(std::vector <GamePositionOnBoard*> *aTetraminoChain, int xPosition, int yPosition);
	void goToNewDirection(std::vector <GamePositionOnBoard*> *aTetraminoChain, int xPosition, int yPosition);

};

