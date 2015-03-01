#include "GameBoard.h"
#include "GameEnums.h"
#include "Tetramino.h"
#include "TetraminoRemovingObserverInterface.h"
#include "TetraminosPositionsDelegate.h"

using namespace std;

GameBoard::GameBoard(int width, int height)
{
	_gameBoardWidth = width;
	_gameBoardHeight = height;
	_observer = NULL;
	_tetramins = vector< vector<Tetramino*> >();
	cleanGameBoard();
	_tetraminosSourceDelegate = new TetraminosPositionsDelegate(&_tetramins);
}

GameBoard::~GameBoard(void)
{
	delete _tetraminosSourceDelegate;
}

void GameBoard::cleanGameBoard(void)
{
	for (int heightIndex = 0; heightIndex < _gameBoardHeight; heightIndex++)
	{
		vector<Tetramino*> tetraminosLine;
		for (int widthIndex = 0; widthIndex < _gameBoardWidth; widthIndex++)
		{
			Tetramino *emptyTetramino = new Tetramino();
			tetraminosLine.push_back(emptyTetramino);
		}
		_tetramins.push_back(tetraminosLine);
	}
}

void GameBoard::replaceTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition)
{
	Tetramino *tetramino = _tetramins[yPosition][xPosition];
	delete tetramino;
	_tetramins[yPosition][xPosition] = aTetramino;
}

void GameBoard::removeTetraminoForXYposition(int xPosition, int yPosition)
{
	Tetramino *newTetramino = new Tetramino();
	_tetramins[yPosition][xPosition] = newTetramino;
}

void GameBoard::removeTetraminoForXYpositionIfItHasNoLives(int xPosition, int yPosition)
{
	Tetramino *tetraminoInBoard = getTetraminoForXYposition(xPosition, yPosition);
	if (tetraminoInBoard->getTetraminoLivesCount() <= 0)
	{
		if (_observer)
		{
			_observer->tetraminoRemoving(tetraminoInBoard);
		}
		removeTetraminoForXYposition(xPosition, yPosition);
		delete tetraminoInBoard;
	}
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

void GameBoard::deleteAllTetraminos()
{
	for (int heightIndex = 0; heightIndex < _gameBoardHeight; heightIndex++)
	{
		for (int widthIndex = 0; widthIndex < _gameBoardWidth; widthIndex++)
		{
			Tetramino *tetraminoInBoard = getTetraminoForXYposition(widthIndex, heightIndex);
			delete tetraminoInBoard;
		}
	}
}

GamePositionOnBoard GameBoard::getPositionForIndex(int aIndex)
{
	int tetraminoColumn = aIndex / _gameBoardWidth;
	int tetraminoRow = aIndex % _gameBoardWidth;
	GamePositionOnBoard positionOnBoard;
	positionOnBoard.xPosition = tetraminoRow;
	positionOnBoard.yPosition = tetraminoColumn;
	return positionOnBoard;
}

int GameBoard::getIndexForPosition(GamePositionOnBoard aPosition)
{
	int positionIndex = aPosition.xPosition  + aPosition.yPosition * _gameBoardWidth;
	return positionIndex;
}

bool GameBoard::positionInBoard(GamePositionOnBoard aPosition)
{
	bool boardWidthPossibility = aPosition.xPosition < _gameBoardWidth && aPosition.xPosition >= 0;
	bool boardHeightPossibility = aPosition.yPosition < _gameBoardHeight && aPosition.yPosition >= 0;
	return (boardWidthPossibility == true && boardHeightPossibility == true);
}

void GameBoard::setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition)
{
	_tetramins[yPosition][xPosition] = aTetramino;
}

int GameBoard::getGameBoardWidth()
{
	return _gameBoardWidth;
}

int GameBoard::getGameBoardHeight()
{
	return _gameBoardHeight;
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

void GameBoard::addObserver(TetraminoRemovingObserverInterface *aObserver)
{
	_observer = aObserver;
}
