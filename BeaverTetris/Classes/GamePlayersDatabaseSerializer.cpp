#include "GamePlayersDatabaseSerializer.h"
#include "SerializersConstants.h"

using namespace std;
using namespace cocos2d;

GamePlayersDatabaseSerializer::GamePlayersDatabaseSerializer(void)
{
	_fileUtils = FileUtils::sharedFileUtils();
	createFile();
}

GamePlayersDatabaseSerializer::~GamePlayersDatabaseSerializer(void)
{
}

void GamePlayersDatabaseSerializer::createFile()
{
	ValueMap databaseData = _fileUtils->getValueMapFromFile(gamePlayersDatabaseDataKey);
	if (databaseData.size() == 0)
	{
		databaseData = ValueMap();
		ValueVector players = ValueVector();
		Value playersValue = Value(players);
		databaseData[gamePlayersKey] = playersValue;
		_fileUtils->writeToFile(databaseData ,gamePlayersDatabaseDataKey);
	}
}

vector<DatabaseInformation> GamePlayersDatabaseSerializer::getDatabaseData()
{
	vector<DatabaseInformation> databaseData;
	ValueMap savedData = _fileUtils->getValueMapFromFile(gamePlayersDatabaseDataKey);
	ValueVector players = savedData[gamePlayersKey].asValueVector();
	fillDatabaseWithPlayers(databaseData, players);
	return databaseData;
}

void GamePlayersDatabaseSerializer::fillDatabaseWithPlayers(vector<DatabaseInformation> &aDatabaseData, ValueVector &aPlayers)
{
	for (int playerIndex = 0; playerIndex < aPlayers.size(); playerIndex++)
	{
		ValueMap playerData = aPlayers[playerIndex].asValueMap();
		DatabaseInformation player;
		player.playerName = playerData[playerNameKey].asString();
		player.playerScore = playerData[playerScoreKey].asInt();
		aDatabaseData.push_back(player);
	}
}

void GamePlayersDatabaseSerializer::saveDatabaseData(vector<DatabaseInformation> &aPlayers)
{
	ValueMap dataToSave = ValueMap();
	ValueVector players = getPlayersInformationFromPlayers(aPlayers);
	dataToSave[gamePlayersKey] = players;
	_fileUtils->writeToFile(dataToSave ,gamePlayersDatabaseDataKey);
}

ValueVector GamePlayersDatabaseSerializer::getPlayersInformationFromPlayers(vector<DatabaseInformation> &aPlayers)
{
	ValueVector players = ValueVector();
	vector<DatabaseInformation>::iterator playersIterator;
	for (playersIterator = aPlayers.begin(); playersIterator != aPlayers.end(); playersIterator++)
	{
		DatabaseInformation player = *playersIterator;
		ValueMap playerData = ValueMap();
		playerData[playerNameKey] = Value(player.playerName);
		playerData[playerScoreKey] = Value(player.playerScore);
		Value playerValue = Value(playerData);
		players.push_back(playerValue);
	}
	return players;
}