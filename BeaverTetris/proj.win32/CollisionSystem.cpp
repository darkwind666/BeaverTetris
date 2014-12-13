#include "CollisionSystem.h"
#include "CollisionDelegate.h"

using namespace std;

CollisionSystem::CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails, GameFlowSystem *aGameFlowController)
{
	_activeDetailsStore = aActiveDetails;
	_gameBoard = aGameBoard;
	_gameFlowController = aGameFlowController;
	_collisionDelegate = new  CollisionDelegate(aGameBoard);
}


CollisionSystem::~CollisionSystem(void)
{
}


void CollisionSystem::updateSystem(float deltaTime)
{
	vector<TetraminoDetail*> tetraminoDetails = _activeDetailsStore->getActiveDetails();

	if (tetraminoDetails.size <= 0)
	{
		_gameFlowController->makeNewGameEvent;
	}

	vector<TetraminoDetail*>::iterator tetraminoDetailsIterator;

	for (tetraminoDetailsIterator = tetraminoDetails.begin; tetraminoDetailsIterator != tetraminoDetails.end; tetraminoDetailsIterator++)
	{
		TetraminoDetail *tetraminoDetail = *tetraminoDetailsIterator;

		TetraminoDetail collidebleTetramino = *tetraminoDetail;
		GamePositionOnBoard newDetailPosition = collidebleTetramino.getDetailPosition;
		newDetailPosition.yPosition = newDetailPosition.yPosition - 1;
		collidebleTetramino.setDetailPosition(newDetailPosition);
		
		if (newDetailPosition.yPosition < 0)
		{
			writeTetraminoDetailInBoard(tetraminoDetail);
		}
		else
		{
			bool collide = _collisionDelegate->checkCollisionWithDetail(collidebleTetramino);
			
			if (collide)
			{
				writeTetraminoDetailInBoard(tetraminoDetail);
			
			}
		}

	}
}

void CollisionSystem::writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail)
{
	for (int yIndex = 0; yIndex < aTetraminoDetail->getDetailHeight; yIndex++)
	{
			
		for (int xIndex = 0; xIndex < aTetraminoDetail->getDetailWidth; xIndex++)
		{			
			Tetramino *tetraminoInDetail = aTetraminoDetail->getTetraminoForXY(xIndex,yIndex);			
			
			if (tetraminoInDetail->getTetraminoType > kTetraminoEmpty)
			{			
				GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();						
				_gameBoard->setTetraminoXYposition(tetraminoInDetail ,detailPosition.xPosition + xIndex, detailPosition.yPosition + yIndex);
			}			
			
		
		}			
			
	}	

	_activeDetailsStore->removeDetail(aTetraminoDetail);

}