#include "GameResultDelegate.h"
#include "WinGameSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GamePlayersDatabase.h"
#include "CurrentLevelDataSource.h"

using namespace std;

GameResultDelegate::GameResultDelegate(WinGameSystem *aWinGameSystem)
{
	_winGameSystem = aWinGameSystem;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_gamePlayersDatabase = (GamePlayersDatabase*)ServiceLocator::getServiceForKey(gamePlayersDatabaseKey);
	_currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
}


GameResultDelegate::~GameResultDelegate(void)
{
}

void GameResultDelegate::gameWasEnded()
{
	if (_winGameSystem->playerWin())
	{
		giveResultToPlayer();
		writePlayerToDatabaseIfFinalLevel();
	}
	saveGameData();
}

void GameResultDelegate::giveResultToPlayer()
{
	GameLevelInformation levelInformation = _currentLevelDataSource->getCurrentLevelData();
	string levelName = levelInformation.levelName;
	int levelAward = levelInformation.levelAward;
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
	_currentPlayerDataSource->setPlayerScore(levelAward + currentPlayerScore);
	_currentPlayerDataSource->completeLevel(levelName);
}

void GameResultDelegate::writePlayerToDatabaseIfFinalLevel()
{
	if (_currentLevelDataSource->finalLevel())
	{
		string playerName = _currentPlayerDataSource->getPlayerName();
		int playerScore = _currentPlayerDataSource->getPlayerScore();
		_gamePlayersDatabase->setPlayerResult(playerName, playerScore);
	}
}

void GameResultDelegate::saveGameData()
{

}