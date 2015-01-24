#include "GameBoard.h"
#include "GameEnums.h"
#include "Tetramino.h"
#include "GameBoardObserverInterface.h"
#include "TetraminosPositionsDelegate.h"

using namespace std;

GameBoard::GameBoard(int width, int height)
{
	_gameBoardWidth = width;
	_gameBoardHeight = height;
	_gameBoardObserver = NULL;
	_tetramins = vector< vector<Tetramino*> >();
	cleanGameBoard();
	_tetraminosSourceDelegate = new TetraminosPositionsDelegate(&_tetramins);
}

GameBoard::~GameBoard(void)
{
	
}

void GameBoard::cleanGameBoard(void)
{
	for (int widthIndex = 0; widthIndex < _gameBoardWidth; widthIndex++)
	{
		vector<Tetramino*> tetraminosLine;
		for (int heightIndex = 0; heightIndex < _gameBoardHeight; heightIndex++)
		{
			Tetramino *emptyTetramino = new Tetramino();
			tetraminosLine.push_back(emptyTetramino);
		}
		_tetramins.push_back(tetraminosLine);
	}

}

void GameBoard::setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition)
{
	_tetramins[xPosition][yPosition] = aTetramino;
}

void GameBoard::replaceTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition)
{
	Tetramino *tetramino = _tetramins[xPosition][yPosition];
	delete tetramino;
	_tetramins[xPosition][yPosition] = aTetramino;
}

int GameBoard::getGameBoardWidth()
{
	return _gameBoardWidth;
}

int GameBoard::getGameBoardHeight()
{
	return _gameBoardHeight;
}

void GameBoard::removeTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *newTetramino = new Tetramino();
	_gameBoardObserver->tetraminoRemoving(_tetramins[xPosition][yPosition]);
	_tetramins[xPosition][yPosition] = newTetramino;
}

void GameBoard::removeTetraminos(std::vector <GamePositionOnBoard> aNeedToRemoveTetraminos)
{
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	for (detailElementsIterator = aNeedToRemoveTetraminos.begin(); detailElementsIterator != aNeedToRemoveTetraminos.end(); detailElementsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *detailElementsIterator;
		removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
}

GamePositionOnBoard GameBoard::getTetraminoPosition(Tetramino *aTetramino)
{
	return _tetraminosSourceDelegate->getTetraminoPosition(aTetramino);
}

Tetramino* GameBoard::getTetraminoForXYposition(int xPosition, int yPosition)
{
	return _tetraminosSourceDelegate->getTetraminoForXYposition(xPosition, yPosition);
}

vector <GamePositionOnBoard> GameBoard::getAvailableTetraminis()
{
	return _tetraminosSourceDelegate->getAvailableTetraminis();
}

vector <GamePositionOnBoard> GameBoard::getTetraminosForType(TetraminoType aTetraminoType)
{
	return _tetraminosSourceDelegate->getTetraminosForType(aTetraminoType);
}

void GameBoard::addObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = aGameBoardObserver;
}

void GameBoard::removeObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = NULL;
}
