#include "RemovingDeadTetraminosSystem.h"
#include "GameStructures.h"
#include <vector>

using namespace std;

RemovingDeadTetraminosSystem::RemovingDeadTetraminosSystem(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


RemovingDeadTetraminosSystem::~RemovingDeadTetraminosSystem(void)
{
}

void RemovingDeadTetraminosSystem::updateSystem(float deltaTime)
{
	vector<GamePositionOnBoard> availableTetraminosPositions = _gameBoard->getAvailableTetraminis();

	vector<GamePositionOnBoard>::iterator positionsIterator;

	for (positionsIterator = availableTetraminosPositions.begin; positionsIterator < availableTetraminosPositions.end; positionsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionsIterator;
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);

		if (tetraminoInBoard->getTetraminoLivesCount <= 0)
		{
			_gameBoard->removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		}

	}

}