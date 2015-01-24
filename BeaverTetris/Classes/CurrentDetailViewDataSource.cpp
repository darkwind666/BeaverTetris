#include "CurrentDetailViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"

CurrentDetailViewDataSource::CurrentDetailViewDataSource(void)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
}


CurrentDetailViewDataSource::~CurrentDetailViewDataSource(void)
{
}

bool CurrentDetailViewDataSource::checkPositionInCurrentDetail(GamePositionOnBoard aPosition)
{
	bool inCurrentDetail = false;
	if (_currentDetailDataSource->currentDetailAvailable())
	{
		bool positionInDetail = positionBelongsToCurrentDetail(aPosition);
		if (positionInDetail)
		{
			inCurrentDetail = availableTetraminoOnPositionInCurrentDetail(aPosition);
		}
	}
	return inCurrentDetail;
}

bool CurrentDetailViewDataSource::positionBelongsToCurrentDetail(GamePositionOnBoard aPosition)
{
	bool positionBelongsToCurrentDetail = true;

	bool widthInterval = inWidthInterval(aPosition);
	bool heightInterval = inHeightInterval(aPosition);

	if (widthInterval == false || heightInterval == false)
	{
		positionBelongsToCurrentDetail = false;
	}
	return positionBelongsToCurrentDetail;
}

bool CurrentDetailViewDataSource::inWidthInterval(GamePositionOnBoard aPosition)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard currentDetailPosition = currentDetail->getDetailPosition();

	bool downWidthInterval = (aPosition.xPosition >= currentDetailPosition.xPosition);
	int detailWidth = currentDetail->getDetailWidth();
	bool upWidthInterval = (aPosition.xPosition < (currentDetailPosition.xPosition + detailWidth));
	bool widthInterval = (downWidthInterval == true && upWidthInterval == true);
	return widthInterval;
}

bool CurrentDetailViewDataSource::inHeightInterval(GamePositionOnBoard aPosition)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard currentDetailPosition = currentDetail->getDetailPosition();

	bool downHeightInterval = (aPosition.yPosition >= currentDetailPosition.yPosition);
	int detailHeight = currentDetail->getDetailHeight();
	bool upHeightInterval = (aPosition.yPosition < (currentDetailPosition.yPosition + detailHeight));
	bool heightInterval = (downHeightInterval == true && upHeightInterval == true);
	return heightInterval;
}

bool CurrentDetailViewDataSource::availableTetraminoOnPositionInCurrentDetail(GamePositionOnBoard aPosition)
{
	bool availableTetraminoInCurrentDetail = false;
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard tetraminoPositionInDetail = currentDetail->convertAbsolutePositionToPositionInDetail(aPosition);
	Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	
	if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
	{
		availableTetraminoInCurrentDetail = true;
	}
	return availableTetraminoInCurrentDetail;
}

TetraminoType CurrentDetailViewDataSource::getTetraminoTypeOnPositionInCurrentDetail(GamePositionOnBoard aPosition)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard tetraminoPositionInDetail = currentDetail->convertAbsolutePositionToPositionInDetail(aPosition);
	Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	return tetraminoInDetail->getTetraminoType();
}