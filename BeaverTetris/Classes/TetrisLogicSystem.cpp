#include "TetrisLogicSystem.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "FullLineCombination.h"
//#include "SimilarTetraminosCombination.h"

using namespace std;

TetrisLogicSystem::TetrisLogicSystem(GameBoard *aGameBoard)
{
	_fullLineCombination = new FullLineCombination(aGameBoard);
	//_similarTetraminosCombination = new SimilarTetraminosCombination(aGameBoard,aCurrentPlayerDataSource);
}


TetrisLogicSystem::~TetrisLogicSystem(void)
{
}

void TetrisLogicSystem::updateSystem(float deltaTime)
{

	_fullLineCombination->checkFullLineCombination();
	//_similarTetraminosCombination->checkSimilarTetraminosCombination();

}