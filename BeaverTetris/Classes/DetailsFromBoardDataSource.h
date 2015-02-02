#pragma once

#include <vector>
#include <map>
#include <functional>
#include "GameStructures.h"
#include "GameEnums.h"

class GameBoard;

class DetailsFromBoardDataSource
{
public:
	DetailsFromBoardDataSource(GameBoard *aGameBoard);
	~DetailsFromBoardDataSource(void);

	std::vector < std::vector <GamePositionOnBoard> > getTetraminoDetailsInGame();

private:

	GameBoard *_gameBoard;
	GameBoard *_extractedDetailsData;

	std::map<DirectionType, std::function<void(GamePositionOnBoard&)> > _waveAlgoritmdirections;

	std::map<DirectionType, std::function<void(GamePositionOnBoard&)> > makeWaveAlgoritmDirections();

	std::vector < std::vector <GamePositionOnBoard> > getAvailableDetailsFromGameBoard();
	void setAvailableDetailsFromGameBoardRowInCollection(int aRow, std::vector < std::vector <GamePositionOnBoard> > *detailsInGameBoard);
	bool checkDetailOnPositionXY(int xPosition, int yPosition);

	std::vector <GamePositionOnBoard> getDetailFromStartPosition(int xPosition, int yPosition);
	void setDetailsInExtractedDetailsData(std::vector <GamePositionOnBoard> aDetailElements);

	void fillTetraminoChainWithPosition(std::vector <GamePositionOnBoard> *aTetraminoChain,  GamePositionOnBoard aPosition);
	void continueFillingTetraminoChainWithPosition(std::vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition);
	bool positionInGameBoard(GamePositionOnBoard aPosition);
	bool nextChainPartOnPosition(std::vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition);
	bool checkPositionInChain(GamePositionOnBoard aPosition, std::vector <GamePositionOnBoard> *aTetraminoChain);
	void goToNewDirection(std::vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition);

	std::vector <GamePositionOnBoard> getDetailElementsFromChain(std::vector <GamePositionOnBoard> *aTetraminoChain);

};

