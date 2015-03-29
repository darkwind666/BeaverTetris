#include "TetraminosInGameBoardViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "KeysForEnumsDataSource.h"
#include "GameFileExtensionMaker.h"
#include "Tetramino.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "StringsSupporter.h"

using namespace std;
using namespace cocos2d;

TetraminosInGameBoardViewDataSource::TetraminosInGameBoardViewDataSource(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}


TetraminosInGameBoardViewDataSource::~TetraminosInGameBoardViewDataSource(void)
{
}

int TetraminosInGameBoardViewDataSource::getTetraminosCount()
{
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	return (gameBoardHeight * gameBoardWidth);
}

string TetraminosInGameBoardViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	TetraminoType tetraminoType = tetraminoInBoard->getTetraminoType();
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

Vec2 TetraminosInGameBoardViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	cocos2d::Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	return Vec2(tetraminoPosition.xPosition * tetraminoOffset.x, tetraminoPosition.yPosition * tetraminoOffset.y);
}

string TetraminosInGameBoardViewDataSource::getTetraminoLivesCountForIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	string livesCount = StringsSupporter::getStringFromNumber(tetraminoInBoard->getTetraminoLivesCount());
	return livesCount;
}

bool TetraminosInGameBoardViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		availableTetramino = false;
	}
	return availableTetramino;
}

bool TetraminosInGameBoardViewDataSource::availableLevesCountOnIndex(int aIndex)
{
	bool availableLevesCount = false;
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty && tetraminoInBoard->getTetraminoType() < kTetraminoBossQueen && tetraminoInBoard->getTetraminoLivesCount() > 1)
	{
		availableLevesCount = true;
	}
	return availableLevesCount;
}
