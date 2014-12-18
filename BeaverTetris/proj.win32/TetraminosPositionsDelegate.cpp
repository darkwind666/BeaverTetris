#include "TetraminosPositionsDelegate.h"

using namespace std;

TetraminosPositionsDelegate::TetraminosPositionsDelegate(Tetramino **tetramins, int boardHeight, int boardWidth)
{
	_tetramins = tetramins;
	_gameBoardHeight = boardHeight;
	_gameBoardWidth = boardWidth;
}


TetraminosPositionsDelegate::~TetraminosPositionsDelegate(void)
{
}

Tetramino* TetraminosPositionsDelegate::getTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *tetramino = _tetramins[yPosition * _gameBoardWidth + xPosition];
	return tetramino;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::getAvailableTetraminis()
{
	vector <GamePositionOnBoard> availableTetraminos = findAllTetraminisForTypeAndPredicate(kTetraminoEmpty, &TetraminosPositionsDelegate::largerType);
	return availableTetraminos;

}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::getTetraminisForType(TetraminoType aTetraminoType)
{
	vector <GamePositionOnBoard> tetraminisForType = findAllTetraminisForTypeAndPredicate(aTetraminoType, &TetraminosPositionsDelegate::equalType);
	return tetraminisForType;
}

vector <GamePositionOnBoard> TetraminosPositionsDelegate::findAllTetraminisForTypeAndPredicate(TetraminoType aTetraminoType, predicateFunction aPredicateFunction)
{
	vector <GamePositionOnBoard> tetraminisForType = vector <GamePositionOnBoard>();
	
	for (int xPosition = 0; xPosition < _gameBoardHeight; xPosition++)
	{
	
		for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
		{
			Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
			if ((this->*aPredicateFunction)(tetramino->getTetraminoType, aTetraminoType))
			{
				GamePositionOnBoard position;
				position.xPosition = xPosition;
				position.yPosition = yPosition;
				tetraminisForType.push_back(position);
			}
	
		}
	
	}
	
	return tetraminisForType;
}

bool TetraminosPositionsDelegate::equalType(TetraminoType aFirstType, TetraminoType aSecondType)
{
	return (aFirstType == aSecondType);
}

bool TetraminosPositionsDelegate::largerType(TetraminoType aFirstType, TetraminoType aSecondType)
{
	return (aFirstType > aSecondType);
}

GamePositionOnBoard TetraminosPositionsDelegate::getTetraminoPosition(Tetramino *aTetramino)
{
	for (int xPosition = 0; xPosition < _gameBoardHeight; xPosition++)
	{
	
		for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
		{
			Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
			if (tetramino == aTetramino)
			{
				GamePositionOnBoard position;
				position.xPosition = xPosition;
				position.yPosition = yPosition;
				return position;
			}
	
		}
	
	}
}



