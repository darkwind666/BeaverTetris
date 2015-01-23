#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
//#include "TetraminisDetailsFactory.h"

CurrentDetailDataSource::CurrentDetailDataSource(void)
{
	//_detailsFactory = new TetraminisDetailsFactory();
	_currentDetailAvailable = true;
	_currentDetail = new TetraminoDetail(3,3);

	GamePositionOnBoard startDetailPosition;
	startDetailPosition.xPosition = 5;
	startDetailPosition.yPosition = 20;

	_currentDetail->setDetailPosition(startDetailPosition);

	Tetramino *newTetraminoRight = new Tetramino(kTetraminoBlue);
	Tetramino *newTetraminoCentre = new Tetramino(kTetraminoBlue);
	Tetramino *newTetraminoLeft = new Tetramino(kTetraminoBlue);

	_currentDetail->setTetraminoForXY(newTetraminoRight ,0,1);
	_currentDetail->setTetraminoForXY(newTetraminoCentre ,1,1);
	_currentDetail->setTetraminoForXY(newTetraminoLeft ,2,1);
}


CurrentDetailDataSource::~CurrentDetailDataSource(void)
{
}

TetraminoDetail* CurrentDetailDataSource::getCurrentDetail()
{
	return _currentDetail;
}

void CurrentDetailDataSource::makeNewDetail(void)
{
	//_currentDetail = _detailsFactory->getNewDetail();
}

void CurrentDetailDataSource::removeCurrentDetail()
{
	delete(_currentDetail);
	_currentDetailAvailable = false;
}

bool CurrentDetailDataSource::currentDetailAvailable()
{
	return _currentDetailAvailable;
}