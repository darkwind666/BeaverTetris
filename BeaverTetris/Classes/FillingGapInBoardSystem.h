#pragma once

#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;
class DetailsFromBoardDataSource;
class TetraminosCombinatorDelegate;
class TetraminoDetailLocatorDelegate;
class CollisionDelegate;
class TetraminoDetail;
class FallenDetailDelegate;

class FillingGapInBoardSystem  : public ServiceInterface
{
public:
	FillingGapInBoardSystem(GameBoard *aGameBoard);
	~FillingGapInBoardSystem(void);

	bool availableGapInBoard();
	void filOutGapInBoard();
	void setDelegate(FallenDetailDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;
	CollisionDelegate *_collisionDelegate;
	FallenDetailDelegate *_delegate;

	bool getAvailableGapInBetweeneDetails(std::vector<TetraminoDetail*> *aDetails);
	bool checkGapUnderDetail(TetraminoDetail *aDetail);
	GamePositionOnBoard getDetailCollisionPosition(TetraminoDetail *aDetail);

	void fillGapsInBoardWithDetails(std::vector<TetraminoDetail*> *aDetails);
	void sendDelegateDetailAndCollisionPosition(TetraminoDetail *aDetail, GamePositionOnBoard aCollisionPosition);
	bool checkPositionsEquality(GamePositionOnBoard aFirstPosition, GamePositionOnBoard aSecondPosition);
	void cleanDetailFromGameBoard(TetraminoDetail *aDetail);
	void cleanDetailColumn(int aColumn, TetraminoDetail *aDetail);
	void cleanDetailTetraminoForPosition(GamePositionOnBoard aPosition, TetraminoDetail *aDetail);
	void removeDetails(std::vector<TetraminoDetail*> *aDetails);
};

