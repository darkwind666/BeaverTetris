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

	_tetraminosType = kTetraminoEmpty;
	_detailForms = vector <  vector< vector<int> >  >();
	_currentDetailFormIndex = 0;
}

TetraminoDetail::TetraminoDetail(TetraminoDetail &copy)
{
	setDetailPosition(copy._position);
	_gameBoardTetraminos = new GameBoard(copy._detailWidth,copy._detailHeight);
	copy.copyTetraminosInDetail(this);
	_detailWidth = copy._detailWidth;
	_detailHeight = copy._detailHeight;
	_tetraminosType = copy._tetraminosType;
	_detailForms = copy._detailForms;
	_currentDetailFormIndex = copy._currentDetailFormIndex;
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
	_currentDetailFormIndex++;
	if (_currentDetailFormIndex >= _detailForms.size())
	{
		_currentDetailFormIndex = 0;
	}
	rotateDetailAccordingToFormIndex();
}

void TetraminoDetail::rotateDetailAccordingToFormIndex()
{
	vector<Tetramino*> emptyTetraminos = getTetraminosForType(kTetraminoEmpty);
	vector<Tetramino*> nonEmptyTetraminos = getTetraminosForType(_tetraminosType);
	fillTetraminosWithFlag(emptyTetraminos, 0);
	fillTetraminosWithFlag(nonEmptyTetraminos, 1);
}

std::vector<Tetramino*> TetraminoDetail::getTetraminosForType(TetraminoType aType)
{
	vector<GamePositionOnBoard> positions = _gameBoardTetraminos->getTetraminosForType(aType);
	vector<Tetramino*> tetraminos;
	vector<GamePositionOnBoard>::iterator positionsIterator;
	for (positionsIterator = positions.begin(); positionsIterator != positions.end(); positionsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionsIterator;
		Tetramino *tetramino = _gameBoardTetraminos->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		tetraminos.push_back(tetramino);
	}
	return tetraminos;
}

void TetraminoDetail::fillTetraminosWithFlag(vector<Tetramino*> &emptyTetraminos, int aFlag)
{
	for (int yIndex = 0; yIndex < _detailHeight; yIndex++)
	{
		fillTetraminosLineFromTetraminosWithFlag(yIndex, emptyTetraminos, aFlag);
	}
}

void TetraminoDetail::fillTetraminosLineFromTetraminosWithFlag(int aLine, vector<Tetramino*> &emptyTetraminos, int aFlag)
{
	vector< vector<int> > detailForm = _detailForms[_currentDetailFormIndex];
	for (int xIndex = 0; xIndex < _detailWidth; xIndex++)
	{
		int tetraminoFlag = detailForm[aLine][xIndex];
		if (tetraminoFlag == aFlag)
		{
			Tetramino *tetramino = emptyTetraminos[0];
			_gameBoardTetraminos->setTetraminoXYposition(tetramino, xIndex, aLine);
			emptyTetraminos.erase(emptyTetraminos.begin());
		}
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

bool TetraminoDetail::absolutePositionInDetail(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard positionInDetail = convertAbsolutePositionToPositionInDetail(aPosition);
	bool inDetail = _gameBoardTetraminos->positionInBoard(positionInDetail);
	return inDetail;
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

void TetraminoDetail::setDetailTetraminosType(TetraminoType aType)
{
	_tetraminosType = aType;
}

void TetraminoDetail::setDetailForms(vector <  vector< vector<int> >  > aDetailForms)
{
	_detailForms = aDetailForms;
}
