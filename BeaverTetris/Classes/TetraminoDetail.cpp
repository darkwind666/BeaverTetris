#include "TetraminoDetail.h"
#include "GameEnums.h"

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

TetraminoDetail::~TetraminoDetail(void)
{
	delete _gameBoardTetraminos;
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

void TetraminoDetail::rotateDetail()
{

	if (_rotatable)
	{
		GameBoard *newGameBoard = new GameBoard(_detailWidth,_detailHeight);
		
		for (int xIndex = 0; xIndex < _detailWidth; xIndex++)
		{
		
			for (int yIndex = 0; yIndex < _detailHeight; yIndex++)
			{
				Tetramino *rotatedTetramino = _gameBoardTetraminos->getTetraminoForXYposition(xIndex, yIndex);
				newGameBoard->setTetraminoXYposition(rotatedTetramino, ((newGameBoard->getGameBoardWidth() - 1) - yIndex), xIndex);
			}
		
		}
		
		_gameBoardTetraminos = newGameBoard;
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