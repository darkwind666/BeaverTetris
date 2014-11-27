#include "CurrentDetailController.h"
#include "CollisionDelegate.h"
#include <vector>

using namespace std;

CurrentDetailController::CurrentDetailController(TetraminisDetailsFactory *detailsFactory, ActiveDetails *activeDetailsStore, GameBoard *aGameBoard)
{
	_detailsFactory = detailsFactory;
	_activeDetailsStore = activeDetailsStore;
	_gameBoard = aGameBoard;
	_collisionDelegate = new CollisionDelegate(aGameBoard);
}


CurrentDetailController::~CurrentDetailController(void)
{
}

void CurrentDetailController::makeNewDetail(void)
{

	_currentDetail = _detailsFactory->getNewDetail();
	_activeDetailsStore->addDetail(_currentDetail);

}

void CurrentDetailController::moveLeftDetail(void)
{
	GamePositionOnBoard currentDetailPosition = _currentDetail->getDetailPosition();

	if (currentDetailPosition.xPosition > 0)
	{
		GamePositionOnBoard newCurrentDetailPosition = currentDetailPosition;
		newCurrentDetailPosition.xPosition = currentDetailPosition.xPosition - 1;
		setNewPositionIfNoCollision(newCurrentDetailPosition);
	}
	
}

void CurrentDetailController::moveRightDetail(void)
{
	GamePositionOnBoard currentDetailPosition = _currentDetail->getDetailPosition();

	if ( (currentDetailPosition.xPosition + _currentDetail->getDetailWidth) > _gameBoard->getGameBoardWidth)
	{
		GamePositionOnBoard newCurrentDetailPosition = currentDetailPosition;
		newCurrentDetailPosition.xPosition = currentDetailPosition.xPosition + 1;
		setNewPositionIfNoCollision(newCurrentDetailPosition);
	}
}

void CurrentDetailController::rotateDetail(void)
{
	TetraminoDetail rotatedTetramino = *_currentDetail;
	rotatedTetramino.rotateDetail();
	bool collide = _collisionDelegate->checkCollisionWithDetail(rotatedTetramino);

	if (!collide)
	{
		_currentDetail->rotateDetail();
	}

}


void CurrentDetailController::setNewPositionIfNoCollision(GamePositionOnBoard aNewDetailPosition)
{
	TetraminoDetail movedTetramino = *_currentDetail;
	movedTetramino.setDetailPosition = aNewDetailPosition;
	bool collide = _collisionDelegate->checkCollisionWithDetail(movedTetramino);

		if (!collide)
		{
			_currentDetail->setDetailPosition(aNewDetailPosition);
		}
}

