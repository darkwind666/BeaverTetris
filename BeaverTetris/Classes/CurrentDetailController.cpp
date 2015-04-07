#include "CurrentDetailController.h"
#include "CollisionDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"
#include <vector>
#include "cocos2d.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailAccelerationDelegate.h"

using namespace std;

CurrentDetailController::CurrentDetailController()
{
	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_gameBoard = gameBoard;
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_collisionDelegate = new CollisionDelegate(gameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(gameBoard);
	_currentDetailAccelerationDelegate = new CurrentDetailAccelerationDelegate();
}


CurrentDetailController::~CurrentDetailController(void)
{
	delete _collisionDelegate;
	delete _tetraminoDetailLocatorDelegate;
	delete _currentDetailAccelerationDelegate;
}

void CurrentDetailController::moveLeftDetail(void)
{
	function<void()> moveLeftDetail = [this](){

		GamePositionOnBoard newDetailPosition = getCurrentDetailPosition();
		newDetailPosition.xPosition = newDetailPosition.xPosition - 1;
		
		if (!checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
		{
			setNewDetailPosition(newDetailPosition);
		}

	};
	makeOperationWithCurrentDetail(moveLeftDetail);
}

void CurrentDetailController::moveRightDetail(void)
{
	function<void()> moveRightDetail = [this](){

		GamePositionOnBoard newDetailPosition = getCurrentDetailPosition();
		newDetailPosition.xPosition = newDetailPosition.xPosition + 1;
		
		if (!checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
		{
			setNewDetailPosition(newDetailPosition);
		}

	};
	makeOperationWithCurrentDetail(moveRightDetail);
}

void CurrentDetailController::rotateDetail(void)
{
	function<void()> rotateDetail = [this](){

		TetraminoDetail *currentDetail = getCurrentDetail();
		TetraminoDetail *rotatedDetail = new TetraminoDetail(*currentDetail);
		rotatedDetail->rotateDetail();
		
		if (!checkCollisionForDetail(rotatedDetail))
		{
			currentDetail->rotateDetail();
		}
		delete rotatedDetail;

	};
	makeOperationWithCurrentDetail(rotateDetail);
}

void CurrentDetailController::throwDetailOnGameBoard()
{
	function<void()> throwDetail = [this](){
		_currentDetailAccelerationDelegate->accelerateCurrentDetail();
	};
	makeOperationWithCurrentDetail(throwDetail);
}

void CurrentDetailController::updateSystem(float deltaTime)
{
	function<void()> moveDownDetail = [this](){
		CurrentDetailController::moveDownDetail();
	};
	makeOperationWithCurrentDetail(moveDownDetail);
	_currentDetailAccelerationDelegate->update();
}

void CurrentDetailController::moveDownDetail()
{
	GamePositionOnBoard newDetailPosition = getCurrentDetailPosition();
	newDetailPosition.yPosition = newDetailPosition.yPosition - 1;

	if (checkCollisionForCurrentDetailWithNewPosition(newDetailPosition))
	{
		writeCurrentDetailInBoardAndRemove();
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

void CurrentDetailController::writeCurrentDetailInBoardAndRemove()
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(currentDetail);
	_currentDetailDataSource->removeCurrentDetail();
	_currentDetailAccelerationDelegate->stopAcceleratingCurrentDetail();
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

void CurrentDetailController::makeOperationWithCurrentDetail(function<void()> aOperation)
{
	if (_currentDetailDataSource->currentDetailAvailable())
	{
		aOperation();
	}
}