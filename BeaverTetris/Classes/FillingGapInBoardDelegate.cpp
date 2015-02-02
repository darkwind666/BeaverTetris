#include "FillingGapInBoardDelegate.h"
#include "GameBoard.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "DetailsFromBoardDataSource.h"
#include "TetraminosCombinatorDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CollisionDelegate.h"

using namespace std;

FillingGapInBoardDelegate::FillingGapInBoardDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(aGameBoard);
	_collisionDelegate = new CollisionDelegate(aGameBoard);
}


FillingGapInBoardDelegate::~FillingGapInBoardDelegate(void)
{
}

void FillingGapInBoardDelegate::filOutGapInBoard()
{
	vector < vector <GamePositionOnBoard> > tetraminoDetailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	vector <TetraminoDetail*> tetraminoDetailsInBoard = _tetraminosCombinatorDelegate->combineTetraminosInDetails(tetraminoDetailsInGame);
	fillGapsInBoardWithDetails(&tetraminoDetailsInBoard);
	removeDetails(&tetraminoDetailsInBoard);
}

void FillingGapInBoardDelegate::fillGapsInBoardWithDetails(vector<TetraminoDetail*> *aDetails)
{
	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aDetails->begin(); detailsIterator != aDetails->end(); detailsIterator++)
	{
		TetraminoDetail *detailInBoard = *detailsIterator;
		cleanDetailFromGameBoard(detailInBoard);
		GamePositionOnBoard detailCollisionPosition = _collisionDelegate->getCollisionPositionWithBoardForDetail(detailInBoard);
		detailInBoard->setDetailPosition(detailCollisionPosition);
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(detailInBoard);
	}
}

void FillingGapInBoardDelegate::cleanDetailFromGameBoard(TetraminoDetail* aDetail)
{
	int detailWidth = aDetail->getDetailWidth();
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		cleanDetailColumn(widthIndex, aDetail);
	}
}

void FillingGapInBoardDelegate::cleanDetailColumn(int aColumn, TetraminoDetail *aDetail)
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

void FillingGapInBoardDelegate::cleanDetailTetraminoForPosition(GamePositionOnBoard aPosition, TetraminoDetail *aDetail)
{
	Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(aPosition.xPosition, aPosition.yPosition);
	TetraminoType tetraminoInDetailType = tetraminoInDetail->getTetraminoType();
	if (tetraminoInDetailType > kTetraminoEmpty)
	{
		GamePositionOnBoard tetraminoPositionInBoard = aDetail->convertPositionInDetailToAbsolutePosition(aPosition);
		_gameBoard->removeTetraminoForXYposition(tetraminoPositionInBoard.xPosition, tetraminoPositionInBoard.yPosition);
	}
}

void FillingGapInBoardDelegate::removeDetails(std::vector<TetraminoDetail*> *aDetails)
{
	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aDetails->begin(); detailsIterator != aDetails->end(); detailsIterator++)
	{
		TetraminoDetail *detailInBoard = *detailsIterator;
		delete detailInBoard;
	}
}
