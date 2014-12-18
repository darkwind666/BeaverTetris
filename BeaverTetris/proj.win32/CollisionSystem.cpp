#include "CollisionSystem.h"
#include "CollisionDelegate.h"

using namespace std;

CollisionSystem::CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails)
{
	_activeDetailsStore = aActiveDetails;
	_gameBoard = aGameBoard;
	_collisionDelegate = new  CollisionDelegate(aGameBoard);
	_tetraminoDetailLocatorDelegate = new TetraminoDetailLocatorDelegate(aGameBoard);
}


CollisionSystem::~CollisionSystem(void)
{
}


void CollisionSystem::updateSystem(float deltaTime)
{
	vector<TetraminoDetail*> tetraminoDetails = _activeDetailsStore->getActiveDetails();

	vector<TetraminoDetail*>::iterator tetraminoDetailsIterator;
	for (tetraminoDetailsIterator = tetraminoDetails.begin(); tetraminoDetailsIterator != tetraminoDetails.end(); tetraminoDetailsIterator++)
	{
		TetraminoDetail *tetraminoDetail = *tetraminoDetailsIterator;

		TetraminoDetail collidebleTetramino = *tetraminoDetail;
		GamePositionOnBoard newDetailPosition = collidebleTetramino.getDetailPosition();
		newDetailPosition.yPosition = newDetailPosition.yPosition - 1;
		collidebleTetramino.setDetailPosition(newDetailPosition);
		
		if (newDetailPosition.yPosition < 0)
		{
			writeTetraminoDetailInBoard(tetraminoDetail);
		}
		else
		{
			bool collide = _collisionDelegate->checkCollisionWithDetail(&collidebleTetramino);
			
			if (collide)
			{
				writeTetraminoDetailInBoard(tetraminoDetail);
			
			}
		}

	}
}

void CollisionSystem::writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail)
{

	_tetraminoDetailLocatorDelegate->writeTetraminoDetailInBoard(aTetraminoDetail);
	_activeDetailsStore->removeDetail(aTetraminoDetail);

}