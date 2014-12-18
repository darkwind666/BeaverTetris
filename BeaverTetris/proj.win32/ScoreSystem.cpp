#include "ScoreSystem.h"
#include "GameDesignConstants.h"

using namespace std;

ScoreSystem::ScoreSystem(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource)
{
	_fullLineCombination = new FullLineCombination(aGameBoard,aCurrentPlayerDataSource);
	_similarTetraminosCombination = new SimilarTetraminosCombination(aGameBoard,aCurrentPlayerDataSource)
}


ScoreSystem::~ScoreSystem(void)
{
}

void ScoreSystem::updateSystem(float deltaTime)
{

	_fullLineCombination->checkFullLineCombination();
	_similarTetraminosCombination->checkSimilarTetraminosCombination();

}