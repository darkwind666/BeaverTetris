#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
//#include "TetraminisDetailsFactory.h"

CurrentDetailDataSource::CurrentDetailDataSource(void)
{
	//_detailsFactory = new TetraminisDetailsFactory();
	_currentDetailAvailable = true;
	_currentDetail = makeNewTetraminoDetail();
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
	_currentDetail = makeNewTetraminoDetail();
	//_currentDetailAvailable = false;
}

bool CurrentDetailDataSource::currentDetailAvailable()
{
	return _currentDetailAvailable;
}

TetraminoDetail* CurrentDetailDataSource::makeNewTetraminoDetail()
{
	TetraminoDetail *newDetail = new TetraminoDetail(3,3);
	
	GamePositionOnBoard startDetailPosition;
	startDetailPosition.xPosition = 7;
	startDetailPosition.yPosition = 20;
	
	newDetail->setDetailPosition(startDetailPosition);
	
	Tetramino *newTetraminoRight = new Tetramino(kTetraminoBlue);
	Tetramino *newTetraminoCentre = new Tetramino(kTetraminoBlue);
	Tetramino *newTetraminoLeft = new Tetramino(kTetraminoBlue);
	
	newDetail->setTetraminoForXY(newTetraminoRight ,0,1);
	newDetail->setTetraminoForXY(newTetraminoCentre ,1,1);
	newDetail->setTetraminoForXY(newTetraminoLeft ,2,1);

	return newDetail;
}