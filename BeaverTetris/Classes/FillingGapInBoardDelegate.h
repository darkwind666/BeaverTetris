#pragma once

#include <vector>
#include "GameStructures.h"

class GameBoard;
class DetailsFromBoardDataSource;
class TetraminosCombinatorDelegate;
class TetraminoDetailLocatorDelegate;
class CollisionDelegate;
class TetraminoDetail;

class FillingGapInBoardDelegate  
{
public:
	FillingGapInBoardDelegate(GameBoard *aGameBoard);
	~FillingGapInBoardDelegate(void);

	void filOutGapInBoard();

private:

	GameBoard *_gameBoard;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;
	CollisionDelegate *_collisionDelegate;

	void fillGapsInBoardWithDetails(std::vector<TetraminoDetail*> *aDetails);
	void cleanDetailFromGameBoard(TetraminoDetail *aDetail);
	void cleanDetailColumn(int aColumn, TetraminoDetail *aDetail);
	void cleanDetailTetraminoForPosition(GamePositionOnBoard aPosition, TetraminoDetail *aDetail);
	void removeDetails(std::vector<TetraminoDetail*> *aDetails);
};

