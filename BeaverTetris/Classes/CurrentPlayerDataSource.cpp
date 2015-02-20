#include "CurrentPlayerDataSource.h"

using namespace std;

CurrentPlayerDataSource::CurrentPlayerDataSource()
{
	_completedLevelsNames = vector <string>();
	_selectedGameLevelIndex = 0;

	PlayerInformation newPlayer;
	newPlayer.playerName = "sasha";
	newPlayer.playerScore = 0;
	_playerData = newPlayer;
	_isThereCurentPlayer = true;

}


CurrentPlayerDataSource::~CurrentPlayerDataSource()
{
}




bool CurrentPlayerDataSource::isThereCurentPlayer()
{
	return _isThereCurentPlayer;
}

string CurrentPlayerDataSource::getPlayerName()
{
	return _playerData.playerName;
}

int CurrentPlayerDataSource::getPlayerScore()
{
	return _playerData.playerScore;
}

int CurrentPlayerDataSource::getPlayerCompletedLevelsCount()
{
	//return _completedLevelsNames.size();
	return 10;
}


int CurrentPlayerDataSource::getPlayerAvailableSpellsCount()
{
	return 4;
}

int CurrentPlayerDataSource::getSelectedGameLevelIndex()
{
	return _selectedGameLevelIndex;
}

void CurrentPlayerDataSource::setNewPlayerWithName(string aNewPlayerName)
{
	PlayerInformation newPlayer;
	newPlayer.playerName = aNewPlayerName;
	newPlayer.playerScore = 0;
	_playerData = newPlayer;
	_isThereCurentPlayer = true;
}	


void CurrentPlayerDataSource::setPlayerScore(int aPlayerScore)
{
	_playerData.playerScore = aPlayerScore;
}

void CurrentPlayerDataSource::setSelectedGameLevelIndex(int aGameLevelIndex)
{
	_selectedGameLevelIndex = aGameLevelIndex;
}

void CurrentPlayerDataSource::completeLevel(string aCompletedLevelName)
{
	vector <string>::iterator it = find(_completedLevelsNames.begin(), _completedLevelsNames.end(), aCompletedLevelName);

	if (it != _completedLevelsNames.end())
	{
		_completedLevelsNames.push_back(aCompletedLevelName);
	}

}

void CurrentPlayerDataSource::cleanPlayer()
{
	PlayerInformation zeroData;
	zeroData.playerName = string("0");
	zeroData.playerScore = 0;
	_playerData = zeroData;
	_isThereCurentPlayer = false;
}


