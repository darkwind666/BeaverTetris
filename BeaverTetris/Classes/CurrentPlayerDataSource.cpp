#include "CurrentPlayerDataSource.h"
#include "CurrentPlayerSerializer.h"
#include "GameLevelsDataSource.h"
#include "GameViewElementsKeys.h"


using namespace std;

CurrentPlayerDataSource::CurrentPlayerDataSource(GameLevelsDataSource *aGameLevelsDataSource)
{
	_gameLevelsDataSource = aGameLevelsDataSource;
	_currentPlayerSerializer = new CurrentPlayerSerializer();
	_allSpellsNames = getAllSpellsNames();
	_completedLevelsNames = vector <string>();
	_availableSpellsNames = vector <string>();
	_selectedGameLevelIndex = 0;
	_isThereCurentPlayer = false;
	setUpPlayer();
}


CurrentPlayerDataSource::~CurrentPlayerDataSource()
{
	delete _currentPlayerSerializer;
}

vector <string> CurrentPlayerDataSource::getAllSpellsNames()
{
	vector <string> allSpellsNames;

	allSpellsNames.push_back(removeCurrentDetailSpellKey);
	allSpellsNames.push_back(firestormSpellKey);
	allSpellsNames.push_back(removeRandomTetraminosSpellKey);
	allSpellsNames.push_back(cohesionSpellKey);

	return allSpellsNames;
}

void CurrentPlayerDataSource::setUpPlayer()
{
	if (_currentPlayerSerializer->availablePlayer())
	{
		_isThereCurentPlayer = true;
		_playerData = _currentPlayerSerializer->getSavedPlayer();
		fillCompletedLevelsNames();
		fillAvailableSpells();
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

void CurrentPlayerDataSource::fillAvailableSpells()
{
	int availableSpellsCount = _playerData.playerAvailableSpellsCount;
	for (int spellIndex = 0; spellIndex < availableSpellsCount; spellIndex++)
	{
		string spellName = _allSpellsNames[spellIndex];
		_availableSpellsNames.push_back(spellName);
	}
}

void CurrentPlayerDataSource::setNewPlayerWithName(string aNewPlayerName)
{
	PlayerInformation newPlayer;
	newPlayer.playerName = aNewPlayerName;
	newPlayer.playerScore = 0;
	newPlayer.playerAvailableSpellsCount = 0;
	newPlayer.playerCompletedLevelsCount = 0;

	_playerData = newPlayer;
	_isThereCurentPlayer = true;
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

void CurrentPlayerDataSource::setNewSpellForKey(string aKey)
{
	vector <string>::iterator it = find(_availableSpellsNames.begin(), _availableSpellsNames.end(), aKey);
	if (it == _availableSpellsNames.end())
	{
		_availableSpellsNames.push_back(aKey);
		_playerData.playerAvailableSpellsCount = _playerData.playerAvailableSpellsCount++;
	}
}

void CurrentPlayerDataSource::cleanPlayer()
{
	PlayerInformation zeroData;
	zeroData.playerName = string("0");
	zeroData.playerScore = 0;
	zeroData.playerAvailableSpellsCount = 0;
	zeroData.playerCompletedLevelsCount = 0;
	_playerData = zeroData;
	_isThereCurentPlayer = false;
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
	return _playerData.playerAvailableSpellsCount;
}

int CurrentPlayerDataSource::getSelectedGameLevelIndex()
{
	return _selectedGameLevelIndex;
}
