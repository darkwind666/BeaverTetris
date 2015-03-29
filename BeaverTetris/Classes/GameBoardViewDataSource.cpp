#include "GameBoardViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "DetailViewDataSource.h"
#include "CurrentDetailTetraminosChecker.h"
#include "CurrentDetailDataSource.h"
#include "TetraminosInGameBoardViewDataSource.h"

using namespace std;
using namespace cocos2d;

GameBoardViewDataSource::GameBoardViewDataSource()
{
	_tetraminosInGameBoardViewDataSource = new TetraminosInGameBoardViewDataSource();
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_currentDetailViewDataSource = getDetailViewDataSource();
	_currentDetailTetraminosChecker = new CurrentDetailTetraminosChecker();
}

GameBoardViewDataSource::~GameBoardViewDataSource(void)
{
	delete _tetraminosInGameBoardViewDataSource;
	delete _currentDetailViewDataSource;
	delete _currentDetailTetraminosChecker;
}

DetailViewDataSource* GameBoardViewDataSource::getDetailViewDataSource()
{
	function<TetraminoDetail*()> detailDataSource = [](){
		CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
		return currentDetailDataSource->getCurrentDetail();
	};
	DetailViewDataSource *detailViewDataSource = new DetailViewDataSource(detailDataSource);
	return detailViewDataSource;
}

int GameBoardViewDataSource::getTetraminosCount()
{
	return _tetraminosInGameBoardViewDataSource->getTetraminosCount();
}

string GameBoardViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	string tetraminoImage;
	if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(aIndex))
	{
		tetraminoImage = _tetraminosInGameBoardViewDataSource->getTetraminoImageForIndex(aIndex);
	}
	else
	{
		GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
		tetraminoImage = _currentDetailViewDataSource->getTetraminoImageForAbsolutePosition(tetraminoPosition);
	}
	return tetraminoImage;
}

Vec2 GameBoardViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	return _tetraminosInGameBoardViewDataSource->getTetraminoPositionForIndex(aIndex);
}

string GameBoardViewDataSource::getTetraminoLivesCountForIndex(int aIndex)
{
	string livesCount;
	if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(aIndex))
	{
		livesCount = _tetraminosInGameBoardViewDataSource->getTetraminoLivesCountForIndex(aIndex);
	}
	else
	{
		GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
		livesCount = _currentDetailViewDataSource->getTetraminoLivesCountOnIndexForAbsolutePosition(tetraminoPosition);
	}
	return livesCount;
}

bool GameBoardViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(aIndex) == false)
	{
		GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
		availableTetramino = _currentDetailTetraminosChecker->checkPositionInCurrentDetail(tetraminoPosition);
	}
	return availableTetramino;
}

bool GameBoardViewDataSource::availableLevesCountOnIndex(int aIndex)
{
	bool availableLevesCount = false;
	if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(aIndex))
	{
		availableLevesCount = _tetraminosInGameBoardViewDataSource->availableLevesCountOnIndex(aIndex);
	}
	else
	{
		GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
		availableLevesCount = _currentDetailViewDataSource->availableLevesCountOnIndexForAbsolutePosition(tetraminoPosition);
	}
	return availableLevesCount;
}