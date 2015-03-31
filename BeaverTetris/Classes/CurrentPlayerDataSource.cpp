#include "CurrentPlayerDataSource.h"
#include "CurrentPlayerSerializer.h"
#include "GameLevelsDataSource.h"

using namespace std;

CurrentPlayerDataSource::CurrentPlayerDataSource(GameLevelsDataSource *aGameLevelsDataSource)
{
	_gameLevelsDataSource = aGameLevelsDataSource;
	_currentPlayerSerializer = new CurrentPlayerSerializer();
	_completedLevelsNames = vector <string>();
	_selectedGameLevelIndex = 0;
	_isThereCurentPlayer = false;
	setUpPlayer();
}


CurrentPlayerDataSource::~CurrentPlayerDataSource()
{
	delete _currentPlayerSerializer;
}

void CurrentPlayerDataSource::setUpPlayer()
{
	if (_currentPlayerSerializer->availablePlayer())
	{
		_isThereCurentPlayer = true;
		_playerData = _currentPlayerSerializer->getSavedPlayer();
		fillCompletedLevelsNames();
	}
}

void CurrentPlayerDataSource::fillCompletedLevelsNames()
{
	int completedLevelsCount = _playerData.playerCompletedLevelsCount;
	for (int levelIndex = 0; levelIndex < completedLevelsCount; levelIndex++)
	{
		string levelName = _gameLevelsDataSource->getLevelNameForIndex(levelIndex);
		_completedLevelsNames.push_back(levelName);
	}
}

void CurrentPlayerDataSource::setNewPlayerWithName(string aNewPlayerName)
{
	PlayerInformation newPlayer;
	newPlayer.playerName = aNewPlayerName;
	newPlayer.playerScore = 0;
	newPlayer.spellsInformation = map<string, int>();
	newPlayer.playerCompletedLevelsCount = 0;

	_playerData = newPlayer;
	_isThereCurentPlayer = true;
	_completedLevelsNames.clear();
	savePlayer();
}	

void CurrentPlayerDataSource::completeLevel(string aCompletedLevelName)
{
	vector <string>::iterator it = find(_completedLevelsNames.begin(), _completedLevelsNames.end(), aCompletedLevelName);
	if (it == _completedLevelsNames.end())
	{
		_completedLevelsNames.push_back(aCompletedLevelName);
		_playerData.playerCompletedLevelsCount = _playerData.playerCompletedLevelsCount++;
	}
}

void CurrentPlayerDataSource::setNewSpellCountForKey(int spellCount, string aKey)
{
	map <string, int>::iterator it = _playerData.spellsInformation.find(aKey);
	if (it == _playerData.spellsInformation.end())
	{
		_playerData.spellsInformation[aKey] = spellCount;
	}
	else
	{
		int currentPlayerSpellCount = it->second;
		if (currentPlayerSpellCount < spellCount)
		{
			_playerData.spellsInformation[aKey] = spellCount;
		}
	}
}

void CurrentPlayerDataSource::cleanPlayer()
{
	PlayerInformation zeroData;
	zeroData.playerName = string("0");
	zeroData.playerScore = 0;
	zeroData.spellsInformation = map<string, int>();
	zeroData.playerCompletedLevelsCount = 0;
	_playerData = zeroData;
	_isThereCurentPlayer = false;
	_completedLevelsNames.clear();
	if (_currentPlayerSerializer->availablePlayer())
	{
		_currentPlayerSerializer->cleanSavedPlayer();
	}
}

void CurrentPlayerDataSource::setPlayerScore(int aPlayerScore)
{
	_playerData.playerScore = aPlayerScore;
}

void CurrentPlayerDataSource::setSelectedGameLevelIndex(int aGameLevelIndex)
{
	_selectedGameLevelIndex = aGameLevelIndex;
}

void CurrentPlayerDataSource::savePlayer()
{
	_currentPlayerSerializer->savePlayer(_playerData);
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
	return _completedLevelsNames.size();
}

int CurrentPlayerDataSource::getPlayerAvailableSpellsCount()
{
	return _playerData.spellsInformation.size();
}

int CurrentPlayerDataSource::getSelectedGameLevelIndex()
{
	return _selectedGameLevelIndex;
}

int CurrentPlayerDataSource::getSpellCountForKey(string aKey)
{
	int spellCount = 0;
	map <string, int>::iterator it = _playerData.spellsInformation.find(aKey);
	if (it != _playerData.spellsInformation.end())
	{
		spellCount = _playerData.spellsInformation[aKey];
	}
	return spellCount;
}