#include "TetraminosSeparatorDelegate.h"

using namespace std;

TetraminosSeparatorDelegate::TetraminosSeparatorDelegate(GameBoard *aGameBoard, ActiveDetails *aActiveDetails)
{
	_gameBoard = aGameBoard;
	_activeDetails = aActiveDetails;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
}


TetraminosSeparatorDelegate::~TetraminosSeparatorDelegate(void)
{

}

void TetraminosSeparatorDelegate::separateTetraminos()
{

	vector < vector <GamePositionOnBoard> > tetraminoDetailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	replaceTetraminosDetailsFromBoardToActiveDetailsStrore(tetraminoDetailsInGame);

}


void TetraminosSeparatorDelegate::replaceTetraminosDetailsFromBoardToActiveDetailsStrore(vector < vector <GamePositionOnBoard> > aTetraminoDetailsInGame)
{

	vector < vector <GamePositionOnBoard> >::iterator tetraminoDetailsInGameIterator;

	for (tetraminoDetailsInGameIterator = aTetraminoDetailsInGame.begin; tetraminoDetailsInGameIterator != aTetraminoDetailsInGame.end; tetraminoDetailsInGameIterator++)
	{
		vector <GamePositionOnBoard> detailElements = *tetraminoDetailsInGameIterator;
		TetraminoDetail *detailFromTetraminos = _tetraminosCombinatorDelegate->combineTetraminosInDetail(detailElements);
		_gameBoard->removeTetraminos(detailElements);
		_activeDetails->addDetail(detailFromTetraminos);

	}

}
