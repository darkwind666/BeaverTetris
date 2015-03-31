#include "CurrentPlayerSerializer.h"
#include <string>
#include "StringsSupporter.h"
#include "SerializersConstants.h"

using namespace cocos2d;
using namespace std;

CurrentPlayerSerializer::CurrentPlayerSerializer(void)
{
	_fileUtils = FileUtils::sharedFileUtils();
	createFile();
}

CurrentPlayerSerializer::~CurrentPlayerSerializer(void)
{
}

void CurrentPlayerSerializer::createFile()
{
	ValueMap playerData = _fileUtils->getValueMapFromFile(currentPlayerDataKey);
	if (playerData.size() == 0)
	{
		playerData = ValueMap();
		_fileUtils->writeToFile(playerData ,currentPlayerDataKey);
	}
}

bool CurrentPlayerSerializer::availablePlayer()
{
	bool available = true;
	ValueMap playerData = _fileUtils->getValueMapFromFile(currentPlayerDataKey);
	if (playerData.size() == 0)
	{
		available = false;
	}
	return available;
}

PlayerInformation CurrentPlayerSerializer::getSavedPlayer()
{
	ValueMap playerData = _fileUtils->getValueMapFromFile(currentPlayerDataKey);
	PlayerInformation player;
	player.playerName = playerData[playerNameKey].asString();
	player.playerScore = playerData[playerScoreKey].asInt();
	player.playerCompletedLevelsCount = playerData[playerCompletedLevelsCountKey].asInt();
	player.spellsInformation = getSpellsInformationFromData(playerData);
	return player;
}

map<string, int> CurrentPlayerSerializer::getSpellsInformationFromData(ValueMap &aData)
{
	map<string, int> spellsInformation;
	ValueMap spellsData = aData[playerSpellsInformationKey].asValueMap();
	ValueMap::iterator spellsIterator;
	for (spellsIterator = spellsData.begin(); spellsIterator != spellsData.end(); spellsIterator++)
	{
		string spellKey = spellsIterator->first;
		int spellCount = spellsIterator->second.asInt();
		spellsInformation[spellKey] = spellCount;
	}
	return spellsInformation;
}

void CurrentPlayerSerializer::savePlayer(PlayerInformation aPlayer)
{
	ValueMap playerData = ValueMap();
	playerData[playerNameKey] = Value(aPlayer.playerName);
	playerData[playerScoreKey] = Value(aPlayer.playerScore);
	playerData[playerCompletedLevelsCountKey] = Value(aPlayer.playerCompletedLevelsCount);
	ValueMap playerSpellsData = getSpellsDataFromPlayer(aPlayer);
	playerData[playerSpellsInformationKey] = Value(playerSpellsData);
	_fileUtils->writeToFile(playerData ,currentPlayerDataKey);
}

ValueMap CurrentPlayerSerializer::getSpellsDataFromPlayer(PlayerInformation &aPlayer)
{
	ValueMap spellsData;
	map<string, int> spellsInformation = aPlayer.spellsInformation;
	map<string, int>::iterator spellsIterator;
	for (spellsIterator = spellsInformation.begin(); spellsIterator != spellsInformation.end(); spellsIterator++)
	{
		string spellKey = spellsIterator->first;
		int spellCount = spellsIterator->second;
		spellsData[spellKey] = Value(spellCount);
	}
	return spellsData;
}

void CurrentPlayerSerializer::cleanSavedPlayer()
{
	Dictionary *playerData = Dictionary::create();
	playerData->writeToFile(currentPlayerDataKey.c_str());
}