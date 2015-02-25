#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "NewTetraminoDetailDataSource.h"

CurrentDetailDataSource::CurrentDetailDataSource(void)
{
	_newTetraminoDetailDataSource = (NewTetraminoDetailDataSource*)ServiceLocator::getServiceForKey(newTetraminoDetailDataSourceKey);
	_currentDetail = NULL;
	_currentDetailAvailable = false;
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
	_currentDetail = _newTetraminoDetailDataSource->getNewDetail();
	_currentDetailAvailable = true;
}

void CurrentDetailDataSource::removeCurrentDetail()
{
	delete(_currentDetail);
	_currentDetail = NULL;
	_currentDetailAvailable = false;
}

bool CurrentDetailDataSource::currentDetailAvailable()
{
	return _currentDetailAvailable;
}
