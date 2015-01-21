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
	int tetraminoColumn = getColumnForIndex(aIndex);
	int tetraminoRow = getRowForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoRow, tetraminoColumn);
	TetraminoType tetraminoType = tetraminoInBoard->getTetraminoType();
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

Vec2 GameBoardViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	int tetraminoColumn = getColumnForIndex(aIndex);
	int tetraminoRow = getRowForIndex(aIndex);
	return Vec2(tetraminoColumn * gameBoardViewColumnOffset, tetraminoRow * gameBoardViewRowOffset);
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
