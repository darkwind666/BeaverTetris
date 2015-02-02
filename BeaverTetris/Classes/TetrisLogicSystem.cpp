#include "TetrisLogicSystem.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "FullLineCombination.h"
//#include "SimilarTetraminosCombination.h"
#include "FillingGapInBoardDelegate.h"

using namespace std;

TetrisLogicSystem::TetrisLogicSystem(GameBoard *aGameBoard)
{
	_fullLineCombination = new FullLineCombination(aGameBoard);
	//_similarTetraminosCombination = new SimilarTetraminosCombination(aGameBoard,aCurrentPlayerDataSource);
	_fillingGapInBoardDelegate = new FillingGapInBoardDelegate(aGameBoard);
}


TetrisLogicSystem::~TetrisLogicSystem(void)
{
}

void TetrisLogicSystem::updateSystem(float deltaTime)
{

	_fullLineCombination->checkFullLineCombination();
	//_similarTetraminosCombination->checkSimilarTetraminosCombination();
	_fillingGapInBoardDelegate->filOutGapInBoard();

}