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

	GamePositionOnBoard currentDetailPosition = getCurrentDetailPosition();

	if (currentDetailPosition.xPosition > 0)
	{
		GamePositionOnBoard newCurrentDetailPosition = currentDetailPosition;
		newCurrentDetailPosition.xPosition = currentDetailPosition.xPosition - 1;
		setNewPositionIfNoCollision(newCurrentDetailPosition);
	}
	
}

void CurrentDetailController::moveRightDetail(void)
{
	GamePositionOnBoard currentDetailPosition = getCurrentDetailPosition();

	int detailNextPosition = currentDetailPosition.xPosition + 1 + getCurrentDetail()->getDetailWidth();

	if (detailNextPosition > _gameBoard->getGameBoardWidth())
	{
		GamePositionOnBoard newCurrentDetailPosition = currentDetailPosition;
		newCurrentDetailPosition.xPosition = currentDetailPosition.xPosition + 1;
		setNewPositionIfNoCollision(newCurrentDetailPosition);
	}
}

void CurrentDetailController::rotateDetail(void)
{
	TetraminoDetail rotatedTetramino = *getCurrentDetail();
	rotatedTetramino.rotateDetail();

	/*
	bool collide = _collisionDelegate->checkCollisionDetailWithOtherTetraminos(&rotatedTetramino);

	if (!collide)
	{
		_currentDetail->rotateDetail();
	}
	*/

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

	bool collisionWithBorders = _collisionDelegate->checkCollisionDetailWithGameBorders(detailWithNewPosition);
	bool collisionWithOtherTetraminos = _collisionDelegate->checkCollisionDetailWithOtherTetraminos(detailWithNewPosition);

	return (collisionWithBorders == true || collisionWithOtherTetraminos == true);
}

void CurrentDetailController::setNewDetailPosition(GamePositionOnBoard aNewDetailPosition)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	currentDetail->setDetailPosition(aNewDetailPosition);
}

void CurrentDetailController::setNewPositionIfNoCollision(GamePositionOnBoard aNewDetailPosition)
{
	/*
	TetraminoDetail movedTetramino = *_currentDetail;
	movedTetramino.setDetailPosition(aNewDetailPosition);
	bool collide = _collisionDelegate->checkCollisionDetailWithOtherTetraminos(&movedTetramino);

	if (!collide)	
	{	
		_currentDetail->setDetailPosition(aNewDetailPosition);	
	}	
	*/

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

