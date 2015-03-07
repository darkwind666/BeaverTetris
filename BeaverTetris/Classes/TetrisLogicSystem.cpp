#include "TetrisLogicSystem.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FullLineCombination.h"
#include "SimilarTetraminosCombination.h"
#include "FillingGapInBoardSystem.h"

using namespace std;

TetrisLogicSystem::TetrisLogicSystem()
{
	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);

	FullLineCombination *fullLineCombinationModel = new FullLineCombination(gameBoard);
	ServiceLocator::setServiceForKey(fullLineCombinationModel, fullLineCombinationModelKey);
	_fullLineCombination = fullLineCombinationModel;

	SimilarTetraminosCombination *similarTetraminosCombinationModel = new SimilarTetraminosCombination(gameBoard);
	ServiceLocator::setServiceForKey(similarTetraminosCombinationModel, similarTetraminosCombinationModelKey);
	_similarTetraminosCombination = similarTetraminosCombinationModel;

	FillingGapInBoardSystem *fillingGapInBoardSystem = new FillingGapInBoardSystem(gameBoard);
	ServiceLocator::setServiceForKey(fillingGapInBoardSystem, fillingGapInBoardSystemKey);
	_fillingGapInBoardDelegate = fillingGapInBoardSystem;
}


TetrisLogicSystem::~TetrisLogicSystem(void)
{
}

void TetrisLogicSystem::updateSystem(float deltaTime)
{
	_fullLineCombination->checkFullLineCombination();
	_similarTetraminosCombination->checkSimilarTetraminosCombination();
	if (_fillingGapInBoardDelegate->availableGapInBoard())
	{
		_fillingGapInBoardDelegate->filOutGapInBoard();
	}
}


