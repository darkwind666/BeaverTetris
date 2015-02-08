#include "TetrisLogicSystem.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FullLineCombination.h"
#include "FillingGapInBoardSystem.h"

using namespace std;

TetrisLogicSystem::TetrisLogicSystem(GameBoard *aGameBoard)
{
	_fullLineCombination = (FullLineCombination*)ServiceLocator::getServiceForKey(fullLineCombinationModelKey);
	_fillingGapInBoardDelegate = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
}


TetrisLogicSystem::~TetrisLogicSystem(void)
{
}

void TetrisLogicSystem::updateSystem(float deltaTime)
{
	
	_fullLineCombination->checkFullLineCombination();
	
	while (_fillingGapInBoardDelegate->availableGapInBoard())
	{
		_fillingGapInBoardDelegate->filOutGapInBoard();
		_fullLineCombination->checkFullLineCombination();
	}

}