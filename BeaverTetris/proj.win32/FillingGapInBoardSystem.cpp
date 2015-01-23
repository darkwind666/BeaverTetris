#include "FillingGapInBoardSystem.h"
#include <vector>

using namespace std;

FillingGapInBoardSystem::FillingGapInBoardSystem(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(aGameBoard);
	_collisionDelegate = new CollisionDelegate(aGameBoard);
}


FillingGapInBoardSystem::~FillingGapInBoardSystem(void)
{
}

void FillingGapInBoardSystem::updateSystem(float deltaTime)
{
	vector < vector <GamePositionOnBoard> > tetraminoDetailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	vector <TetraminoDetail*> tetraminoDetailsInBoard = _tetraminosCombinatorDelegate->combineTetraminosInDetails(tetraminoDetailsInGame);
	//_gameBoard->cleanGameBoard();
	fillGapsInBoardWithDetails(&tetraminoDetailsInBoard);
}

void FillingGapInBoardSystem::fillGapsInBoardWithDetails(vector<TetraminoDetail*> *aTetraminoDetailsInGame)
{

	vector<TetraminoDetail*>::iterator tetraminoDetailsInGameIterator;

	for (tetraminoDetailsInGameIterator = aTetraminoDetailsInGame->begin(); tetraminoDetailsInGameIterator != aTetraminoDetailsInGame->end(); tetraminoDetailsInGameIterator++)
	{
		TetraminoDetail *detailInBoard = *tetraminoDetailsInGameIterator;
		GamePositionOnBoard detailCollisionPosition = _collisionDelegate->getCollisionPositionWithBoardForDetail(detailInBoard);
		detailInBoard->setDetailPosition(detailCollisionPosition);
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(detailInBoard);
	}

}

