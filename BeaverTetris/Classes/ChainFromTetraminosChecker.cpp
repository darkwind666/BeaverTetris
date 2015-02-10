#include "ChainFromTetraminosChecker.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"

using namespace std;

ChainFromTetraminosChecker::ChainFromTetraminosChecker(void)
{
}


ChainFromTetraminosChecker::~ChainFromTetraminosChecker(void)
{
}

vector<GamePositionOnBoard> ChainFromTetraminosChecker::getChainFromTetraminosPositions(vector<GamePositionOnBoard> aPositions, TetraminoDetail *aDetail)
{
	vector< vector<GamePositionOnBoard> > chains;
	vector<GamePositionOnBoard> chain;
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aPositions.begin(); tetraminosIterator != aPositions.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			GamePositionOnBoard absoluteTetraminoPosition = aDetail->convertPositionInDetailToAbsolutePosition(tetraminoPosition);
			chain.push_back(absoluteTetraminoPosition);
		}
		else
		{
			vector<GamePositionOnBoard> chainFromPositions = chain;
			chains.push_back(chainFromPositions);
			chain.clear();
		}
	}
	chains.push_back(chain);
	sortChains(chains);
	return chains[0];
}

void ChainFromTetraminosChecker::sortChains(std::vector< std::vector<GamePositionOnBoard> > &aChains)
{
	sort(aChains.begin(), aChains.end(), [](vector<GamePositionOnBoard> &chainA, vector<GamePositionOnBoard> &chainB){
		return (chainA.size() > chainB.size());
	});
}