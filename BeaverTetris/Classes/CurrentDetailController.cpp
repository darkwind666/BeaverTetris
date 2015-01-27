#include "CurrentDetailController.h"
#include "CollisionDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"
#include <vector>
#include "cocos2d.h"

using namespace std;

CurrentDetailController::CurrentDetailController(GameBoard *aGameBoard, CurrentDetailDataSource *aDetailDataSource)
{
	_gameBoard = aGameBoard;
	_currentDetailDataSource = aDetailDataSource;
	_collisionDelegate = new CollisionDelegate(aGameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(aGameBoard);
}


CurrentDetailController::~CurrentDetailController(void)
{
}

void CurrentDetailController::moveLeftDetail(void)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	GamePositionOnBoard newDetailPosition = currentDetail->getDetailPosition();
	newDetailPosition.xPosition = newDetailPosition.xPosition - 1;
	
	if (!checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
	{
		setNewDetailPosition(newDetailPosition);
	}
	
}

void CurrentDetailController::moveRightDetail(void)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	GamePositionOnBoard newDetailPosition = currentDetail->getDetailPosition();
	newDetailPosition.xPosition = newDetailPosition.xPosition + 1;
	
	if (!checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
	{
		setNewDetailPosition(newDetailPosition);
	}
}

void CurrentDetailController::rotateDetail(void)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	TetraminoDetail *rotatedDetail = new TetraminoDetail(*currentDetail);
	rotatedDetail->rotateDetail();

	if (!checkCollisionForDetail(rotatedDetail))
	{
		currentDetail->rotateDetail();
	}
	delete rotatedDetail;
}

void CurrentDetailController::updateSystem(float deltaTime)
{
	if (_currentDetailDataSource->currentDetailAvailable())
	{
		moveDownDetail();
	}
}

void CurrentDetailController::moveDownDetail()
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	GamePositionOnBoard newDetailPosition = currentDetail->getDetailPosition();
	newDetailPosition.yPosition = newDetailPosition.yPosition - 1;

	if (checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
	{
		_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(currentDetail);
		_currentDetailDataSource->removeCurrentDetail();
	}
	else
	{
		setNewDetailPosition(newDetailPosition);
	}
}

bool CurrentDetailController::checkCollisionForCurrentDetailWithNewPosition(GamePositionOnBoard aNewDetailPosition)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	TetraminoDetail *detailWithNewPosition = new TetraminoDetail((*currentDetail));
	detailWithNewPosition->setDetailPosition(aNewDetailPosition);
	bool collisionWithDetail = checkCollisionForDetail(detailWithNewPosition);
	delete detailWithNewPosition;
	return collisionWithDetail;
}

bool CurrentDetailController::checkCollisionForDetail(TetraminoDetail *aDetail)
{
	bool collisionWithBorders = _collisionDelegate->checkCollisionDetailWithGameBorders(aDetail);
	bool collisionWithOtherTetraminos = _collisionDelegate->checkCollisionDetailWithOtherTetraminos(aDetail);
	return (collisionWithBorders == true || collisionWithOtherTetraminos == true);
}

void CurrentDetailController::setNewDetailPosition(GamePositionOnBoard aNewDetailPosition)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	currentDetail->setDetailPosition(aNewDetailPosition);
}

TetraminoDetail* CurrentDetailController::getCurrentDetail()
{
	return _currentDetailDataSource->getCurrentDetail();
}

GamePositionOnBoard CurrentDetailController::getCurrentDetailPosition()
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	return currentDetail->getDetailPosition();
}

