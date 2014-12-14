#include "TetraminosFallEvent.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "TetraminoDetail.h"
#include "CollisionDelegate.h"

using namespace std;

TetraminosFallEvent::TetraminosFallEvent(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminisDetailsFactory = (TetraminisDetailsFactory*)ServiceLocator::getServiceForKey(tetraminisDetailsFactoryKey);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(_gameBoard);
	_currentUpdateState = 0;
}


TetraminosFallEvent::~TetraminosFallEvent(void)
{
}

bool TetraminosFallEvent::eventTime(void)
{
	bool eventTime = false;

	if (_currentUpdateState >= tetraminosFallEventTimeIntervalConstant)
	{
		eventTime = true;
	}
	return eventTime;
}

void TetraminosFallEvent::runEvent(void)
{
	vector<TetraminoDetail*> tetraminoDetails = getTetraminoDetailsForFalling();
	placeDetailsOnGameBoard(tetraminoDetails);
	_currentUpdateState = 0;

}

void TetraminosFallEvent::updateEvent(void)
{
	_currentUpdateState++;
}

vector<TetraminoDetail*> TetraminosFallEvent::getTetraminoDetailsForFalling()
{
	vector<TetraminoDetail*> tetraminoDetails;

	for (int detailIndex = 0; detailIndex <= tetraminosFallEventDetailsCountConstant; detailIndex++)
	{
		TetraminoDetail *newDetail = getNewDetailFromWidthIndex(detailIndex);
		tetraminoDetails.push_back(newDetail);
		
	}
	return tetraminoDetails;
}

TetraminoDetail* TetraminosFallEvent::getNewDetailFromWidthIndex(int aWidthIndex)
{
	TetraminoDetail *newDetail = _tetraminisDetailsFactory->getNewDetail;

	GamePositionOnBoard detailPosition;
	detailPosition.yPosition = _gameBoard->getGameBoardHeight - newDetail->getDetailHeight;
	detailPosition.xPosition = newDetail->getDetailWidth * aWidthIndex;

	newDetail->setDetailPosition(detailPosition);
	return newDetail;
}

void TetraminosFallEvent::placeDetailsOnGameBoard(vector<TetraminoDetail*> aTetraminoDetails)
{
	CollisionDelegate *collisionDelegate = new CollisionDelegate(_gameBoard);

	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aTetraminoDetails.begin; detailsIterator != aTetraminoDetails.end; detailsIterator++)
	{
		TetraminoDetail *tetraminoDetail = *detailsIterator;
		GamePositionOnBoard detailCollisionPosition = collisionDelegate->getCollisionPositionWithBoardForDetail(tetraminoDetail);
		tetraminoDetail->setDetailPosition(detailCollisionPosition);
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(tetraminoDetail);
	}

}