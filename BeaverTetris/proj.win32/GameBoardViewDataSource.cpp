#include "GameBoardViewDataSource.h"
#include "GameFileExtensionMaker.h"

int gameBoardViewColumnOffset = 4;
int gameBoardViewRowOffset = 4;

using namespace std;
using namespace cocos2d;

GameBoardViewDataSource::GameBoardViewDataSource(GameBoard *aGameBoard, KeysForEnumsDataSource *aKeysForEnumsDataSource)
{
	_gameBoard = aGameBoard;
	_keysForEnumsDataSource = aKeysForEnumsDataSource;
}


GameBoardViewDataSource::~GameBoardViewDataSource(void)
{
}

int GameBoardViewDataSource::getTetraminosCount()
{
	return (_gameBoard->getGameBoardHeight * _gameBoard->getGameBoardWidth);
}

string GameBoardViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	int tetraminoColumn = getColumnForIndex(aIndex);
	int tetraminoRow = getRowForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoRow, tetraminoColumn);
	TetraminoType tetraminoType = tetraminoInBoard->getTetraminoType;
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
	int boardWidth = _gameBoard->getGameBoardWidth;
	return aIndex / boardWidth;
}

int GameBoardViewDataSource::getRowForIndex(int aIndex)
{
	int boardWidth = _gameBoard->getGameBoardWidth;
	return aIndex % boardWidth;
}
