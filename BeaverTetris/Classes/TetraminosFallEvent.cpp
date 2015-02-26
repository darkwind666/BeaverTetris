#include "TetraminosFallEvent.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "TetraminoDetail.h"
#include "CollisionDelegate.h"
#include "NewTetraminoDetailDataSource.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "GameBoard.h"
#include "GameHelper.h"
#include "FallenDetailDelegate.h"

using namespace std;

TetraminosFallEvent::TetraminosFallEvent(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_newTetraminoDetailDataSource = (NewTetraminoDetailDataSource*)ServiceLocator::getServiceForKey(newTetraminoDetailDataSourceKey);
	_collisionDelegate = new CollisionDelegate(_gameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(_gameBoard);
	_currentUpdateState = 0;
	_delegate = NULL;
}


TetraminosFallEvent::~TetraminosFallEvent(void)
{
}

void TetraminosFallEvent::updateEvent(void)
{
	_currentUpdateState++;
	if (_currentUpdateState >= tetraminosFallEventTimeIntervalConstant)
	{
		vector<TetraminoDetail*> tetraminoDetails = getTetraminoDetailsForFalling();
		placeDetailsOnGameBoard(tetraminoDetails);
		_currentUpdateState = 0;
	}
}

vector<TetraminoDetail*> TetraminosFallEvent::getTetraminoDetailsForFalling()
{
	vector<TetraminoDetail*> tetraminoDetails;
	for (int detailIndex = 0; detailIndex <= tetraminosFallEventDetailsCountConstant; detailIndex++)
	{
		TetraminoDetail *newDetail = getNewDetail();
		tetraminoDetails.push_back(newDetail);
	}
	return tetraminoDetails;
}

TetraminoDetail* TetraminosFallEvent::getNewDetail()
{
	TetraminoDetail *newDetail = _newTetraminoDetailDataSource->getNewDetail();
	setDetailPosition(newDetail);
	return newDetail;
}

void TetraminosFallEvent::setDetailPosition(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	int detailWidth = aDetail->getDetailWidth();
	int detailXPosition = GameHelper::getRandomNumberFromUpInterval(gameBoardWidth - detailWidth);
	detailPosition.xPosition = detailXPosition;
	aDetail->setDetailPosition(detailPosition);
}

void TetraminosFallEvent::placeDetailsOnGameBoard(vector<TetraminoDetail*> aTetraminoDetails)
{
	vector<TetraminoDetail*>::iterator detailsIterator;
	for (detailsIterator = aTetraminoDetails.begin(); detailsIterator != aTetraminoDetails.end(); detailsIterator++)
	{
		TetraminoDetail *tetraminoDetail = *detailsIterator;
		GamePositionOnBoard detailCollisionPosition = _collisionDelegate->getCollisionPositionWithBoardForDetail(tetraminoDetail);
		sendMessageToDelegateWithDetailAndCollisionPosition(tetraminoDetail, detailCollisionPosition);
		tetraminoDetail->setDetailPosition(detailCollisionPosition);
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(tetraminoDetail);
	}
}

void TetraminosFallEvent::sendMessageToDelegateWithDetailAndCollisionPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	if (_delegate)
	{
		_delegate->placeNewDetailToPosition(aDetail, aPosition);
	}
}

void TetraminosFallEvent::setDelegate(FallenDetailDelegate *aDelegate)
{
	_delegate = aDelegate;
}