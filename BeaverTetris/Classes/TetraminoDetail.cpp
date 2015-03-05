#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "GameEnums.h"
#include "GameBoard.h"

using namespace std;

TetraminoDetail::TetraminoDetail(int width, int height)
{
	_gameBoardTetraminos = new GameBoard(width,height);
	_detailWidth = width;
	_detailHeight = height;
	_rotatable = true;

	GamePositionOnBoard position;
	position.xPosition = width;
	position.yPosition = height;
	_position = position;
}

TetraminoDetail::TetraminoDetail(TetraminoDetail &copy)
{
	setDetailPosition(copy._position);
	_gameBoardTetraminos = new GameBoard(copy._detailWidth,copy._detailHeight);
	copy.copyTetraminosInDetail(this);
	_detailWidth = copy._detailWidth;
	_detailHeight = copy._detailHeight;
}

TetraminoDetail::~TetraminoDetail(void)
{
	delete _gameBoardTetraminos;
}

void TetraminoDetail::copyTetraminosInDetail(TetraminoDetail *aDestinationDetail)
{
	for (int xIndex = 0; xIndex < _detailWidth; xIndex++)
	{
		for (int yIndex = 0; yIndex < _detailHeight; yIndex++)
		{
			Tetramino *rotatedTetramino = _gameBoardTetraminos->getTetraminoForXYposition(xIndex, yIndex);
			aDestinationDetail->setTetraminoForXY(rotatedTetramino, xIndex, yIndex);
		}
	}
}

void TetraminoDetail::rotateDetail()
{
	if (_rotatable)
	{
		rotateDetailBoard();
	}
}

void TetraminoDetail::rotateDetailBoard()
{
	GameBoard *newGameBoard = new GameBoard(_detailWidth,_detailHeight);
	for (int xIndex = 0; xIndex < _detailWidth; xIndex++)
	{
		rotateColumnAndPlaceInNewBoard(xIndex, newGameBoard);
	}
	
	delete _gameBoardTetraminos;
	_gameBoardTetraminos = newGameBoard;
}

void TetraminoDetail::rotateColumnAndPlaceInNewBoard(int aColumn, GameBoard *aGameBoard)
{
	for (int yIndex = 0; yIndex < _detailHeight; yIndex++)
	{
		Tetramino *rotatedTetramino = _gameBoardTetraminos->getTetraminoForXYposition(aColumn, yIndex);
		aGameBoard->replaceTetraminoXYposition(rotatedTetramino, yIndex, aColumn);
	}
}

GamePositionOnBoard TetraminoDetail::convertPositionInDetailToAbsolutePosition(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard currentDetailPosition = this->getDetailPosition();
	
	GamePositionOnBoard tetraminoPositionInDetail;
	tetraminoPositionInDetail.xPosition = currentDetailPosition.xPosition + aPosition.xPosition;
	tetraminoPositionInDetail.yPosition = currentDetailPosition.yPosition + aPosition.yPosition;
	return tetraminoPositionInDetail;
}

GamePositionOnBoard TetraminoDetail::convertAbsolutePositionToPositionInDetail(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard currentDetailPosition = this->getDetailPosition();
	
	GamePositionOnBoard tetraminoPositionInDetail;
	tetraminoPositionInDetail.xPosition = aPosition.xPosition - currentDetailPosition.xPosition;
	tetraminoPositionInDetail.yPosition = aPosition.yPosition - currentDetailPosition.yPosition;
	return tetraminoPositionInDetail;
}

int TetraminoDetail::getDetailWidth()
{
	return _detailWidth;
}

int TetraminoDetail::getDetailHeight()
{
	return _detailHeight;
}

Tetramino* TetraminoDetail::getTetraminoForXY(int xPosition, int yPosition)
{
	return _gameBoardTetraminos->getTetraminoForXYposition(xPosition, yPosition);
}

GamePositionOnBoard TetraminoDetail::getDetailPosition()
{
	return _position;
}

vector<GamePositionOnBoard> TetraminoDetail::getAvailableTetraminos()
{
	return _gameBoardTetraminos->getAvailableTetraminis();
}

void TetraminoDetail::setTetraminoForXY(Tetramino *aTetramino, int xPosition, int yPosition)
{
	_gameBoardTetraminos->replaceTetraminoXYposition(aTetramino,xPosition,yPosition);
}

void TetraminoDetail::setDetailPosition(GamePositionOnBoard aDetailPosition)
{
	_position = aDetailPosition;
}

void TetraminoDetail::setDetailRotatebleFlag(bool aRotatable)
{
	_rotatable = aRotatable;
}

GamePositionOnBoard TetraminoDetail::getPositionForIndex(int aIndex)
{
	return _gameBoardTetraminos->getPositionForIndex(aIndex);
}

int TetraminoDetail::getIndexForPosition(GamePositionOnBoard aPosition)
{
	return _gameBoardTetraminos->getIndexForPosition(aPosition);
}