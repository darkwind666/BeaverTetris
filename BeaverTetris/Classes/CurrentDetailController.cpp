#include "CurrentDetailController.h"
#include "CollisionDelegate.h"
#include "TetraminoDetailLocatorDelegate.h"
#include "CurrentDetailControllerDelegate.h"
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
	_delegate = NULL;
}


CurrentDetailController::~CurrentDetailController(void)
{
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

		TetraminoDetail *currentDetail = getCurrentDetail();
		GamePositionOnBoard finalCurrentDetailPositionOnBoard = _collisionDelegate->getCollisionPositionWithBoardForDetail(currentDetail);
		if (_delegate)
		{
			_delegate->throwCurrentDetailOnPosition(finalCurrentDetailPositionOnBoard);
		}
		setNewDetailPosition(finalCurrentDetailPositionOnBoard);
		writeCurrentDetailInBoardAndRemove();

	};
	makeOperationWithCurrentDetail(throwDetail);
}

void CurrentDetailController::setDelegate(CurrentDetailControllerDelegate *aDelegate)
{
	_delegate = aDelegate;
}

void CurrentDetailController::updateSystem(float deltaTime)
{
	function<void()> moveDownDetail = [this](){
		CurrentDetailController::moveDownDetail();
	};
	makeOperationWithCurrentDetail(moveDownDetail);
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