#include "CurrentPlayerSpellsDelegate.h"
#include "GameDesignConstants.h"

using namespace std;

CurrentPlayerSpellsDelegate::CurrentPlayerSpellsDelegate(void)
{
	_playerSpells = map<string, LevelSpellInformation>();
}


CurrentPlayerSpellsDelegate::~CurrentPlayerSpellsDelegate(void)
{
}

void CurrentPlayerSpellsDelegate::setNewPlayerSpells(map<string, LevelSpellInformation> aSpells)
{
	_playerSpells = aSpells;
}

map<string, LevelSpellInformation> CurrentPlayerSpellsDelegate::getPlayerSpells()
{
	return _playerSpells;
}

void CurrentPlayerSpellsDelegate::cleanPlayerSpells()
{
	_playerSpells = map<string, LevelSpellInformation>();
}


int CurrentPlayerSpellsDelegate::getSpellCountForKey(string aKey)
{
	LevelSpellInformation spellInformation = getSpellInformationForKey(aKey);
	return spellInformation.spellCount;
}

int CurrentPlayerSpellsDelegate::getSpellRechargeIntervalForKey(string aKey)
{
	LevelSpellInformation spellInformation = getSpellInformationForKey(aKey);
	return spellInformation.spellRechargeInterval;
}

LevelSpellInformation CurrentPlayerSpellsDelegate::getSpellInformationForKey(string aKey)
{
	LevelSpellInformation spellInformation;
	spellInformation.spellCount = 0;
	spellInformation.spellRechargeInterval = maxSpellRechargeInterval;
	map <string, LevelSpellInformation>::iterator it = _playerSpells.find(aKey);
	if (it != _playerSpells.end())
	{
		spellInformation = _playerSpells[aKey];
	}
	return spellInformation;
}

void CurrentPlayerSpellsDelegate::setNewSpellCountForKey(int spellCount, string aKey)
{
	LevelSpellInformation spellInformation;
	spellInformation.spellCount = spellCount;
	spellInformation.spellRechargeInterval = maxSpellRechargeInterval;
	setNewSpellInformationForKey(spellInformation, aKey);
}

void CurrentPlayerSpellsDelegate::setNewSpellRechargeIntervalForKey(int spellRechargeInterval, string aKey)
{
	LevelSpellInformation spellInformation;
	spellInformation.spellCount = 0;
	spellInformation.spellRechargeInterval = spellRechargeInterval;
	setNewSpellInformationForKey(spellInformation, aKey);
}

void CurrentPlayerSpellsDelegate::setNewSpellInformationForKey(LevelSpellInformation aSpellInformation, string aKey)
{
	map <string, LevelSpellInformation>::iterator it = _playerSpells.find(aKey);
	if (it == _playerSpells.end())
	{
		_playerSpells[aKey] = aSpellInformation;
	}
	else
	{
		setSpellInformationForKey(aSpellInformation, aKey);
	}
}

void CurrentPlayerSpellsDelegate::setSpellInformationForKey(LevelSpellInformation aSpellInformation, string aKey)
{
	int currentPlayerSpellCount = _playerSpells[aKey].spellCount;
	if (currentPlayerSpellCount < aSpellInformation.spellCount)
	{
		_playerSpells[aKey].spellCount = aSpellInformation.spellCount;
	}
	
	int currentPlayerSpellInterval = _playerSpells[aKey].spellRechargeInterval;
	if (currentPlayerSpellInterval > aSpellInformation.spellRechargeInterval)
	{
		_playerSpells[aKey].spellRechargeInterval = aSpellInformation.spellRechargeInterval;
	}
}