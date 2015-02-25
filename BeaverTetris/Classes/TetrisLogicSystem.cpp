#include "TetrisLogicSystem.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FullLineCombination.h"
#include "SimilarTetraminosCombination.h"
#include "FillingGapInBoardSystem.h"

using namespace std;

TetrisLogicSystem::TetrisLogicSystem(GameBoard *aGameBoard)
{
	_fullLineCombination = (FullLineCombination*)ServiceLocator::getServiceForKey(fullLineCombinationModelKey);
	_similarTetraminosCombination = (SimilarTetraminosCombination*)ServiceLocator::getServiceForKey(similarTetraminosCombinationModelKey);
	_fillingGapInBoardDelegate = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
	_updatable = true;
}


TetrisLogicSystem::~TetrisLogicSystem(void)
{
}

void TetrisLogicSystem::updateSystem(float deltaTime)
{
	if (_updatable)
	{
		updateGameLogic();
	}
}

void TetrisLogicSystem::updateGameLogic()
{
	_fullLineCombination->checkFullLineCombination();
	_similarTetraminosCombination->checkSimilarTetraminosCombination();
	
	while (_fillingGapInBoardDelegate->availableGapInBoard())
	{
		_fullLineCombination->checkFullLineCombination();
		_similarTetraminosCombination->checkSimilarTetraminosCombination();
		_fillingGapInBoardDelegate->filOutGapInBoard();
	}
}

void TetrisLogicSystem::setUpdatable(bool aUpdatable)
{
	_updatable = aUpdatable;
}