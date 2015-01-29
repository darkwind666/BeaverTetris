#include "CurrentDetailTetraminosChecker.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"

CurrentDetailTetraminosChecker::CurrentDetailTetraminosChecker()
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
}

CurrentDetailTetraminosChecker::~CurrentDetailTetraminosChecker(void)
{
}

bool CurrentDetailTetraminosChecker::checkPositionInCurrentDetail(GamePositionOnBoard aPosition)
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

bool CurrentDetailTetraminosChecker::positionBelongsToCurrentDetail(GamePositionOnBoard aPosition)
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

bool CurrentDetailTetraminosChecker::inWidthInterval(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard currentDetailPosition = getCurrentDetail()->getDetailPosition();

	bool downWidthInterval = (aPosition.xPosition >= currentDetailPosition.xPosition);
	int detailWidth = getCurrentDetail()->getDetailWidth();
	bool upWidthInterval = (aPosition.xPosition < (currentDetailPosition.xPosition + detailWidth));
	bool widthInterval = (downWidthInterval == true && upWidthInterval == true);
	return widthInterval;
}

bool CurrentDetailTetraminosChecker::inHeightInterval(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard currentDetailPosition = getCurrentDetail()->getDetailPosition();

	bool downHeightInterval = (aPosition.yPosition >= currentDetailPosition.yPosition);
	int detailHeight = getCurrentDetail()->getDetailHeight();
	bool upHeightInterval = (aPosition.yPosition < (currentDetailPosition.yPosition + detailHeight));
	bool heightInterval = (downHeightInterval == true && upHeightInterval == true);
	return heightInterval;
}

bool CurrentDetailTetraminosChecker::availableTetraminoOnPositionInCurrentDetail(GamePositionOnBoard aPosition)
{
	bool availableTetraminoInCurrentDetail = false;
	GamePositionOnBoard tetraminoPositionInDetail = getCurrentDetail()->convertAbsolutePositionToPositionInDetail(aPosition);
	Tetramino *tetraminoInDetail = getCurrentDetail()->getTetraminoForXY(tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	
	if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
	{
		availableTetraminoInCurrentDetail = true;
	}
	return availableTetraminoInCurrentDetail;
}

TetraminoDetail* CurrentDetailTetraminosChecker::getCurrentDetail()
{
	return _currentDetailDataSource->getCurrentDetail();
}