#include "CurrentDetailDataSource.h"
//#include "TetraminisDetailsFactory.h"

CurrentDetailDataSource::CurrentDetailDataSource(void)
{
	//_detailsFactory = new TetraminisDetailsFactory();
	_currentDetailAvailable = true
}


CurrentDetailDataSource::~CurrentDetailDataSource(void)
{
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