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
	player.completedTutorials = getCompletedTutorialsInformationFromData(playerData);
	return player;
}

map<string, LevelSpellInformation> CurrentPlayerSerializer::getSpellsInformationFromData(ValueMap &aData)
{
	map<string, LevelSpellInformation> spellsInformation;
	ValueMap spellsData = aData[playerSpellsInformationKey].asValueMap();
	ValueMap::iterator spellsIterator;
	for (spellsIterator = spellsData.begin(); spellsIterator != spellsData.end(); spellsIterator++)
	{
		string spellKey = spellsIterator->first;
		ValueMap spellData = spellsIterator->second.asValueMap();
		LevelSpellInformation spellInformation;
		spellInformation.spellCount = spellData[playerSpellCountKey].asInt();
		spellInformation.spellRechargeInterval = spellData[playerSpellRechargeIntervalKey].asInt();
		spellsInformation[spellKey] = spellInformation;
	}
	return spellsInformation;
}

vector<string> CurrentPlayerSerializer::getCompletedTutorialsInformationFromData(cocos2d::ValueMap &aData)
{
	vector<string> completedTutorialsInformation;
	ValueVector tutorialsData = aData[playerTutorialsInformationKey].asValueVector();
	ValueVector::iterator tutorialsIterator;
	for (tutorialsIterator = tutorialsData.begin(); tutorialsIterator != tutorialsData.end(); tutorialsIterator++)
	{
		Value tutorial = *tutorialsIterator;
		completedTutorialsInformation.push_back(tutorial.asString());
	}
	return completedTutorialsInformation;
}

void CurrentPlayerSerializer::savePlayer(PlayerInformation aPlayer)
{
	ValueMap playerData = ValueMap();
	playerData[playerNameKey] = Value(aPlayer.playerName);
	playerData[playerScoreKey] = Value(aPlayer.playerScore);
	playerData[playerCompletedLevelsCountKey] = Value(aPlayer.playerCompletedLevelsCount);
	ValueMap playerSpellsData = getSpellsDataFromPlayer(aPlayer);
	playerData[playerSpellsInformationKey] = Value(playerSpellsData);
	ValueVector playerTutorialsData = getTutorialsDataFromPlayer(aPlayer);
	playerData[playerTutorialsInformationKey] = Value(playerTutorialsData);
	_fileUtils->writeToFile(playerData ,currentPlayerDataKey);
}

ValueMap CurrentPlayerSerializer::getSpellsDataFromPlayer(PlayerInformation &aPlayer)
{
	ValueMap spellsData;
	map<string, LevelSpellInformation> spellsInformation = aPlayer.spellsInformation;
	map<string, LevelSpellInformation>::iterator spellsIterator;
	for (spellsIterator = spellsInformation.begin(); spellsIterator != spellsInformation.end(); spellsIterator++)
	{
		string spellKey = spellsIterator->first;
		LevelSpellInformation spellInformation = spellsIterator->second;
		ValueMap spellData;
		spellData[playerSpellCountKey] = spellInformation.spellCount;
		spellData[playerSpellRechargeIntervalKey] = spellInformation.spellRechargeInterval;
		spellsData[spellKey] = Value(spellData);
	}
	return spellsData;
}

ValueVector CurrentPlayerSerializer::getTutorialsDataFromPlayer(PlayerInformation &aPlayer)
{
	ValueVector tutorialsData;
	vector<string> tutorialsInformation = aPlayer.completedTutorials;
	vector<string>::iterator tutorialsIterator;
	for (tutorialsIterator = tutorialsInformation.begin(); tutorialsIterator != tutorialsInformation.end(); tutorialsIterator++)
	{
		string tutorialKey = *tutorialsIterator;
		Value tutorialData = Value(tutorialKey);
		tutorialsData.push_back(tutorialData);
	}
	return tutorialsData;
}

void CurrentPlayerSerializer::cleanSavedPlayer()
{
	Dictionary *playerData = Dictionary::create();
	playerData->writeToFile(currentPlayerDataKey.c_str());
}