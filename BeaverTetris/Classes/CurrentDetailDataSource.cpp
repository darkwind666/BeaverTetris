#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "NewTetraminoDetailDataSource.h"

CurrentDetailDataSource::CurrentDetailDataSource(void)
{
	_newTetraminoDetailDataSource = new NewTetraminoDetailDataSource();
	_currentDetailAvailable = true;
	_currentDetail = _newTetraminoDetailDataSource->getNewDetail();
}


CurrentDetailDataSource::~CurrentDetailDataSource(void)
{
}

TetraminoDetail* CurrentDetailDataSource::getCurrentDetail()
{
	return _currentDetail;
}

GamePositionOnBoard CurrentDetailDataSource::getCurrentDetailPosition()
{
	return _currentDetail->getDetailPosition();
}

void CurrentDetailDataSource::makeNewDetail(void)
{
	
}

void CurrentDetailDataSource::removeCurrentDetail()
{
	delete(_currentDetail);
	_currentDetail = _newTetraminoDetailDataSource->getNewDetail();
	_currentDetailAvailable = true;
}

bool CurrentDetailDataSource::currentDetailAvailable()
{
	return _currentDetailAvailable;
}
