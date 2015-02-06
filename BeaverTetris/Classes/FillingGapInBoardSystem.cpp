#include "FillingGapInBoardSystem.h"
#include "GameBoard.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "DetailsFromBoardDataSource.h"
#include "TetraminosCombinatorDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CollisionDelegate.h"
#include "FillingGapInBoardDelegate.h"

using namespace std;

FillingGapInBoardSystem::FillingGapInBoardSystem(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(aGameBoard);
	_collisionDelegate = new CollisionDelegate(aGameBoard);
	_delegate = NULL;
}


FillingGapInBoardSystem::~FillingGapInBoardSystem(void)
{
}

void FillingGapInBoardSystem::filOutGapInBoard()
{
	vector < vector <GamePositionOnBoard> > tetraminoDetailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	vector <TetraminoDetail*> tetraminoDetailsInBoard = _tetraminosCombinatorDelegate->combineTetraminosInDetails(tetraminoDetailsInGame);
	fillGapsInBoardWithDetails(&tetraminoDetailsInBoard);
	removeDetails(&tetraminoDetailsInBoard);
}

void FillingGapInBoardSystem::fillGapsInBoardWithDetails(vector<TetraminoDetail*> *aDetails)
{
	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aDetails->begin(); detailsIterator != aDetails->end(); detailsIterator++)
	{
		TetraminoDetail *detailInBoard = *detailsIterator;
		cleanDetailFromGameBoard(detailInBoard);
		GamePositionOnBoard detailCollisionPosition = _collisionDelegate->getCollisionPositionWithBoardForDetail(detailInBoard);
		sendDelegateDetailAndCollisionPosition(detailInBoard, detailCollisionPosition);
		detailInBoard->setDetailPosition(detailCollisionPosition);
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(detailInBoard);
	}
}

void FillingGapInBoardSystem::cleanDetailFromGameBoard(TetraminoDetail* aDetail)
{
	int detailWidth = aDetail->getDetailWidth();
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		cleanDetailColumn(widthIndex, aDetail);
	}
}

void FillingGapInBoardSystem::cleanDetailColumn(int aColumn, TetraminoDetail *aDetail)
{
	int detailHeight = aDetail->getDetailHeight();
	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{
		GamePositionOnBoard tetraminoPositionInDetail;
		tetraminoPositionInDetail.xPosition = aColumn;
		tetraminoPositionInDetail.yPosition = heightIndex;
		cleanDetailTetraminoForPosition(tetraminoPositionInDetail, aDetail);
	}
}

void FillingGapInBoardSystem::cleanDetailTetraminoForPosition(GamePositionOnBoard aPosition, TetraminoDetail *aDetail)
{
	Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(aPosition.xPosition, aPosition.yPosition);
	TetraminoType tetraminoInDetailType = tetraminoInDetail->getTetraminoType();
	if (tetraminoInDetailType > kTetraminoEmpty)
	{
		GamePositionOnBoard tetraminoPositionInBoard = aDetail->convertPositionInDetailToAbsolutePosition(aPosition);
		_gameBoard->removeTetraminoForXYposition(tetraminoPositionInBoard.xPosition, tetraminoPositionInBoard.yPosition);
	}
}

void  FillingGapInBoardSystem::sendDelegateDetailAndCollisionPosition(TetraminoDetail *aDetail, GamePositionOnBoard aCollisionPosition)
{
	bool positionsEqual = checkPositionsEquality(aDetail->getDetailPosition(), aCollisionPosition);
	if (_delegate && positionsEqual == false)
	{
		_delegate->replaceDetailToPosition(aDetail, aCollisionPosition);
	}
}

bool FillingGapInBoardSystem::checkPositionsEquality(GamePositionOnBoard aFirstPosition, GamePositionOnBoard aSecondPosition)
{
	bool equalX = (aFirstPosition.xPosition == aSecondPosition.xPosition);
	bool equalY = (aFirstPosition.yPosition == aSecondPosition.yPosition);
	return (equalX == true && equalY == true);
}

void FillingGapInBoardSystem::removeDetails(std::vector<TetraminoDetail*> *aDetails)
{
	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aDetails->begin(); detailsIterator != aDetails->end(); detailsIterator++)
	{
		TetraminoDetail *detailInBoard = *detailsIterator;
		delete detailInBoard;
	}
}

void FillingGapInBoardSystem::setDelegate(FillingGapInBoardDelegate *aDelegate)
{
	_delegate = aDelegate;
}