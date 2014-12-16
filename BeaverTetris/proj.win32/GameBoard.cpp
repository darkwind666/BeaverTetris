#include "GameBoard.h"
#include "GameEnums.h"

using namespace std;

GameBoard::GameBoard(int width, int height)
{
	_gameBoardWidth = width;
	_gameBoardHeight = height;
	cleanGameBoard();
}


GameBoard::~GameBoard(void)
{
}


void GameBoard::setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition)
{
	_tetramins[yPosition * _gameBoardWidth + xPosition] = aTetramino;
}

int GameBoard::getGameBoardWidth()
{
	return _gameBoardWidth;
}

int GameBoard::getGameBoardHeight()
{
	return _gameBoardHeight;
}

Tetramino* GameBoard::getTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *tetramino = _tetramins[yPosition * _gameBoardWidth + xPosition];
	return tetramino;
}

GamePositionOnBoard GameBoard::getTetraminoPosition(Tetramino *aTetramino)
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

vector <GamePositionOnBoard> GameBoard::getAvailableTetraminis()
{

	vector <GamePositionOnBoard> availableTetraminos = vector <GamePositionOnBoard>();

	for (int xPosition = 0; xPosition < _gameBoardHeight; xPosition++)
	{

		for (int yPosition = 0; yPosition < _gameBoardWidth; yPosition++)
		{
			Tetramino *tetramino = getTetraminoForXYposition(xPosition,yPosition);
			if (tetramino->getTetraminoType() > kTetraminoEmpty)
			{
				GamePositionOnBoard position;
				position.xPosition = xPosition;
				position.yPosition = yPosition;
				availableTetraminos.push_back(position);
			}

		}

	}

	return availableTetraminos;

}

void GameBoard::removeTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *newTetramino = new Tetramino();
	int teraminoIndex = xPosition * _gameBoardWidth + yPosition;
	_gameBoardObserver->tetraminoRemoving(_tetramins[teraminoIndex]);
	_tetramins[teraminoIndex] = newTetramino;
}

void GameBoard::removeTetraminos(std::vector <GamePositionOnBoard> aNeedToRemoveTetraminos)
{
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	
	for (detailElementsIterator = aNeedToRemoveTetraminos.begin; detailElementsIterator != aNeedToRemoveTetraminos.end; detailElementsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *detailElementsIterator;
		removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
}

void GameBoard::cleanTetraminoRowForYposition(int yPosition)
{
	for (int xPosition = 0; xPosition < _gameBoardWidth; xPosition++)
	{
		removeTetraminoForXYposition(xPosition, yPosition);
	}
}

void GameBoard::cleanGameBoard(void)
{

	int tetraminosCount = _gameBoardHeight * _gameBoardWidth;
	_tetramins = new Tetramino*[_gameBoardHeight * _gameBoardWidth];

	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		Tetramino *cleanTetramino = new Tetramino();
		_tetramins[tetraminoIndex] = cleanTetramino;

	}

	
}

void GameBoard::addObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = aGameBoardObserver;
}

void GameBoard::removeObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = NULL;
}