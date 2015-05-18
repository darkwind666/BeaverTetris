#include "CurrentPlayerDataSource.h"
#include "CurrentPlayerSerializer.h"
#include "GameLevelsDataSource.h"
#include "CurrentPlayerSpellsDelegate.h"

using namespace std;

CurrentPlayerDataSource::CurrentPlayerDataSource(GameLevelsDataSource *aGameLevelsDataSource)
{
	_gameLevelsDataSource = aGameLevelsDataSource;
	_currentPlayerSerializer = new CurrentPlayerSerializer();
	_completedLevelsNames = vector <string>();
	_selectedGameLevelIndex = 0;
	_isThereCurentPlayer = false;
	_currentPlayerSpellsDelegate = new CurrentPlayerSpellsDelegate();
	setUpPlayer();
}

CurrentPlayerDataSource::~CurrentPlayerDataSource()
{
	delete _currentPlayerSerializer;
	delete _currentPlayerSpellsDelegate;
}

void CurrentPlayerDataSource::setUpPlayer()
{
	if (_currentPlayerSerializer->availablePlayer())
	{
		_isThereCurentPlayer = true;
		_playerData = _currentPlayerSerializer->getSavedPlayer();
		_currentPlayerSpellsDelegate->setNewPlayerSpells(_playerData.spellsInformation);
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
	newPlayer.spellsInformation = map<string, LevelSpellInformation>();
	newPlayer.playerCompletedLevelsCount = 0;

	_playerData = newPlayer;
	_isThereCurentPlayer = true;
	_completedLevelsNames.clear();
	_currentPlayerSpellsDelegate->cleanPlayerSpells();
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

void CurrentPlayerDataSource::cleanPlayer()
{
	PlayerInformation zeroData;
	zeroData.playerName = string("0");
	zeroData.playerScore = 0;
	zeroData.spellsInformation = map<string, LevelSpellInformation>();
	zeroData.playerCompletedLevelsCount = 0;
	_playerData = zeroData;
	_isThereCurentPlayer = false;
	_completedLevelsNames.clear();
	_currentPlayerSpellsDelegate->cleanPlayerSpells();
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
	_playerData.spellsInformation = _currentPlayerSpellsDelegate->getPlayerSpells();
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
	int completedLevelsCount = 0;
	if (_isThereCurentPlayer)
	{
		completedLevelsCount = _completedLevelsNames.size();
	}
	return completedLevelsCount;
}

int CurrentPlayerDataSource::getPlayerAvailableSpellsCount()
{

	return _currentPlayerSpellsDelegate->getPlayerSpells().size();
}

int CurrentPlayerDataSource::getSelectedGameLevelIndex()
{
	return _selectedGameLevelIndex;
}

int CurrentPlayerDataSource::getSpellCountForKey(string aKey)
{
	return _currentPlayerSpellsDelegate->getSpellCountForKey(aKey);
}

int CurrentPlayerDataSource::getSpellRechargeIntervalForKey(string aKey)
{
	return _currentPlayerSpellsDelegate->getSpellRechargeIntervalForKey(aKey);
}

void CurrentPlayerDataSource::setNewSpellCountForKey(int spellCount, string aKey)
{
	_currentPlayerSpellsDelegate->setNewSpellCountForKey(spellCount, aKey);
}

void CurrentPlayerDataSource::setNewSpellRechargeIntervalForKey(int spellRechargeInterval, string aKey)
{
	_currentPlayerSpellsDelegate->setNewSpellRechargeIntervalForKey(spellRechargeInterval, aKey);
}
