#include "GameBoard.h"
#include "GameEnums.h"

using namespace std;

GameBoard::GameBoard(int width, int height)
{
	_gameBoardWidth = width;
	_gameBoardHeight = height;
	_tetraminosSourceDelegate = new TetraminosPositionsDelegate(_tetramins, height, width);
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
	
	for (detailElementsIterator = aNeedToRemoveTetraminos.begin(); detailElementsIterator != aNeedToRemoveTetraminos.end(); detailElementsIterator++)
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

vector <GamePositionOnBoard> GameBoard::getTetraminisForType(TetraminoType aTetraminoType)
{
	return _tetraminosSourceDelegate->getTetraminisForType(aTetraminoType);
}


void GameBoard::addObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = aGameBoardObserver;
}

void GameBoard::removeObserver(GameBoardObserverInterface *aGameBoardObserver)
{
	_gameBoardObserver = NULL;
}