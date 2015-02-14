#include "TetraminosPositionsDelegate.h"
#include "Tetramino.h"

using namespace std;

TetraminosPositionsDelegate::TetraminosPositionsDelegate(std::vector< std::vector<Tetramino*> > *tetraminos)
{
	_tetraminos = tetraminos;
	_gameBoardHeight = _tetraminos->size();
	_gameBoardWidth = _tetraminos[0].size();
}

TetraminosPositionsDelegate::~TetraminosPositionsDelegate(void)
{
}

Tetramino* TetraminosPositionsDelegate::getTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *tetramino = (*_tetraminos)[yPosition][xPosition];
	return tetramino;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::getAvailableTetraminis()
{
	vector <GamePositionOnBoard> availableTetraminos = findAllTetraminisForPredicate([](Tetramino *aTetramino){
		return (aTetramino->getTetraminoType() > kTetraminoEmpty);
	});
	return availableTetraminos;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::getTetraminosForType(TetraminoType aTetraminoType)
{
	vector <GamePositionOnBoard> tetraminisForType = findAllTetraminisForPredicate([aTetraminoType](Tetramino *aTetramino){
		return (aTetramino->getTetraminoType() == aTetraminoType);
	});
	return tetraminisForType;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::findAllTetraminisForPredicate(function<bool(Tetramino *aTetramino)> aPredicateFunction)
{
	vector <GamePositionOnBoard> tetraminisForType = vector <GamePositionOnBoard>();
	
	for (int xPosition = 0; xPosition < _gameBoardHeight; xPosition++)
	{
		vector <GamePositionOnBoard> tetraminisForTypeInRow = getTetraminosInRowWithPredicate(xPosition, aPredicateFunction);
		tetraminisForType.insert(tetraminisForType.end(), tetraminisForTypeInRow.begin(), tetraminisForTypeInRow.end());
	}
	
	return tetraminisForType;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::getTetraminosInRowWithPredicate(int xPosition, function<bool(Tetramino *aTetramino)> aPredicateFunction)
{
	vector <GamePositionOnBoard> tetraminisForTypeInRow = vector <GamePositionOnBoard>();
	for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
	{
		Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
		if (aPredicateFunction(tetramino))
		{
			GamePositionOnBoard position;
			position.xPosition = xPosition;
			position.yPosition = yPosition;
			tetraminisForTypeInRow.push_back(position);
		}
	}
	return tetraminisForTypeInRow;
}

GamePositionOnBoard TetraminosPositionsDelegate::getTetraminoPosition(Tetramino *aTetramino)
{
	GamePositionOnBoard tetraminoPosition;
	for (int xPosition = 0; xPosition < _gameBoardHeight; xPosition++)
	{
		bool inRow = checkTetraminoInRow(aTetramino, xPosition);
		if (inRow)
		{
			tetraminoPosition = getTetraminoPositionInRow(aTetramino, xPosition);
			break;
		}
	}
	return tetraminoPosition;
}

bool TetraminosPositionsDelegate::checkTetraminoInRow(Tetramino *aTetramino, int xPosition)
{
	bool inRow = false;
	for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
	{
		Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
		if (tetramino == aTetramino)
		{
			inRow = true;
			break;
		}
	
	}
	return inRow;
}

GamePositionOnBoard TetraminosPositionsDelegate::getTetraminoPositionInRow(Tetramino *aTetramino, int xPosition)
{
	GamePositionOnBoard position;
	position.xPosition = xPosition;
	position.yPosition = 0;
	for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
	{
		Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
		if (tetramino == aTetramino)
		{
			position.yPosition = yPosition;
			return position;
		}
	}
}


