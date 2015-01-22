#include "GameBoardViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "KeysForEnumsDataSource.h"
#include "GameFileExtensionMaker.h"
#include "Tetramino.h"

const int gameBoardViewColumnOffset = 4;
const int gameBoardViewRowOffset = 4;

using namespace std;
using namespace cocos2d;

GameBoardViewDataSource::GameBoardViewDataSource()
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}


GameBoardViewDataSource::~GameBoardViewDataSource(void)
{
}

int GameBoardViewDataSource::getTetraminosCount()
{
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	return (gameBoardHeight * gameBoardWidth);
}

string GameBoardViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	TetraminoType tetraminoType = tetraminoInBoard->getTetraminoType();
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

Vec2 GameBoardViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = getPositionForIndex(aIndex);
	return Vec2(tetraminoPosition.yPosition * gameBoardViewColumnOffset, tetraminoPosition.xPosition * gameBoardViewRowOffset);
}

bool GameBoardViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	GamePositionOnBoard tetraminoPosition = getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		availableTetramino = false;
	}
	return availableTetramino;
}

GamePositionOnBoard GameBoardViewDataSource::getPositionForIndex(int aIndex)
{
	int tetraminoColumn = getColumnForIndex(aIndex);
	int tetraminoRow = getRowForIndex(aIndex);
	GamePositionOnBoard positionOnBoard;
	positionOnBoard.xPosition = tetraminoRow;
	positionOnBoard.yPosition = tetraminoColumn;
	return positionOnBoard;
}

int GameBoardViewDataSource::getColumnForIndex(int aIndex)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	return aIndex / boardWidth;
}

int GameBoardViewDataSource::getRowForIndex(int aIndex)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	return aIndex % boardWidth;
}
