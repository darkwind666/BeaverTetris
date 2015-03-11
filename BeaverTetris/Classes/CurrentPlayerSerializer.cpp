#include "CurrentPlayerSerializer.h"
#include <string>
#include "StringsSupporter.h"

using namespace cocos2d;
using namespace std;

const string currentPlayerDataKey = string("CurrentPlayerData.plist");
const string playerNameKey = string("PlayerName");
const string playerScoreKey = string("PlayerScore");
const string playerAvailableSpellsCountKey = string("PlayerAvailableSpellsCount");
const string playerCompletedLevelsCountKey = string("PlayerCompletedLevelsCount");

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
	player.playerAvailableSpellsCount = playerData[playerAvailableSpellsCountKey].asInt();
	player.playerCompletedLevelsCount = playerData[playerCompletedLevelsCountKey].asInt();
	return player;
}

void CurrentPlayerSerializer::savePlayer(PlayerInformation aPlayer)
{
	ValueMap playerData = ValueMap();
	playerData[playerNameKey] = Value(aPlayer.playerName);
	playerData[playerScoreKey] = Value(aPlayer.playerScore);
	playerData[playerAvailableSpellsCountKey] = Value(aPlayer.playerAvailableSpellsCount);
	playerData[playerCompletedLevelsCountKey] = Value(aPlayer.playerCompletedLevelsCount);
	_fileUtils->writeToFile(playerData ,currentPlayerDataKey);
}

void CurrentPlayerSerializer::cleanSavedPlayer()
{
	Dictionary *playerData = Dictionary::create();
	playerData->writeToFile(currentPlayerDataKey.c_str());
}