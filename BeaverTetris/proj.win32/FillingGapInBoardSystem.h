#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "DetailsFromBoardDataSource.h"
#include "TetraminosCombinatorDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CollisionDelegate.h"
#include <vector>


class FillingGapInBoardSystem :public GameSystemInterface
{
public:
	FillingGapInBoardSystem(GameBoard *aGameBoard);
	~FillingGapInBoardSystem(void);

	void updateSystem(float deltaTime);

private:

	GameBoard *_gameBoard;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;
	CollisionDelegate *_collisionDelegate;

	void fillGapsInBoardWithDetails(std::vector<TetraminoDetail*> *aTetraminoDetailsInGame);

};

