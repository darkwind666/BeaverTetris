#include "GameBoardViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "CurrentDetailViewDataSource.h"
#include "KeysForEnumsDataSource.h"
#include "GameFileExtensionMaker.h"
#include "Tetramino.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

GameBoardViewDataSource::GameBoardViewDataSource()
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_currentDetailViewDataSource = new CurrentDetailViewDataSource();
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
	TetraminoType tetraminoType = getVisibleTetraminoTypeOnPosition(tetraminoPosition);
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

TetraminoType GameBoardViewDataSource::getVisibleTetraminoTypeOnPosition(GamePositionOnBoard aPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	TetraminoType tetraminoType = tetraminoInBoard->getTetraminoType();
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		tetraminoType = _currentDetailViewDataSource->getTetraminoTypeOnPositionInCurrentDetail(aPosition);
	}
	return tetraminoType;
}

Vec2 GameBoardViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	cocos2d::Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	GamePositionOnBoard tetraminoPosition = getPositionForIndex(aIndex);
	return Vec2(tetraminoPosition.xPosition * tetraminoOffset.x, tetraminoPosition.yPosition * tetraminoOffset.y);
}

bool GameBoardViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	GamePositionOnBoard tetraminoPosition = getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		availableTetramino = _currentDetailViewDataSource->checkPositionInCurrentDetail(tetraminoPosition);
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