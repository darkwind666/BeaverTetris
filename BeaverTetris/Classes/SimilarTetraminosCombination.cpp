#include "SimilarTetraminosCombination.h"
#include "DetailsFromBoardDataSource.h"
#include "TetraminosChainCleaner.h"
#include "ChainFromTetraminosChecker.h"
#include "HorisontalChainChecker.h"
#include "VerticalChainChecker.h"

using namespace std;

SimilarTetraminosCombination::SimilarTetraminosCombination(GameBoard *aGameBoard)
{

	_tetraminosChainCleaner = new TetraminosChainCleaner(aGameBoard);
	_chainFromTetraminosChecker = new ChainFromTetraminosChecker();
	_horisontalChainChecker = new HorisontalChainChecker(_tetraminosChainCleaner, aGameBoard);
	_verticalChainChecker = new VerticalChainChecker(_tetraminosChainCleaner, aGameBoard);
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
}


SimilarTetraminosCombination::~SimilarTetraminosCombination(void)
{
	delete _detailsFromBoardDataSource;
	delete _chainFromTetraminosChecker;
	delete _tetraminosChainCleaner;
	delete _horisontalChainChecker;
	delete _verticalChainChecker;
}

void SimilarTetraminosCombination::checkSimilarTetraminosCombination()
{
	vector < vector <GamePositionOnBoard> > detailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	vector < vector <GamePositionOnBoard> >::iterator detailsInGameIterator;
	for (detailsInGameIterator = detailsInGame.begin(); detailsInGameIterator != detailsInGame.end(); detailsInGameIterator++)
	{
		checkChainInDetailElements(*detailsInGameIterator);
	}
}

void SimilarTetraminosCombination::checkChainInDetailElements(vector<GamePositionOnBoard> aTetraminos)
{
	_horisontalChainChecker->checkChainInDetailHorisontals(aTetraminos);
	_verticalChainChecker->checkChainInDetailVerticals(aTetraminos);
}

void SimilarTetraminosCombination::setDelegate(ExplosionAnimationDelegate *aDelegate)
{
	_tetraminosChainCleaner->setDelegate(aDelegate);
}
