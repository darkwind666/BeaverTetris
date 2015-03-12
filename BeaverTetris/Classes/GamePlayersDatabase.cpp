#include "GamePlayersDatabase.h"
#include "GamePlayersDatabaseSerializer.h"
#include <algorithm>

using namespace std;

bool sortFunction(const DatabaseInformation &left, const DatabaseInformation &right);

GamePlayersDatabase::GamePlayersDatabase(void)
{
	_gamePlayersDatabaseSerializer = new GamePlayersDatabaseSerializer();
	_players = _gamePlayersDatabaseSerializer->getDatabaseData();
}

GamePlayersDatabase::~GamePlayersDatabase(void)
{
	delete _gamePlayersDatabaseSerializer;
}

int GamePlayersDatabase::getPlayersCount()
{
	return _players.size();
}

string GamePlayersDatabase::getPlayerNameForIndex(int aIndex)
{
	DatabaseInformation player = _players[aIndex];
	return player.playerName;
}

int GamePlayersDatabase::getPlayerScoreForIndex(int aIndex)
{
	DatabaseInformation player = _players[aIndex];
	return player.playerScore;
}


void GamePlayersDatabase::setPlayerResult(string aPlayerName, int playerScore)
{
	DatabaseInformation player;
	player.playerName = aPlayerName;
	player.playerScore = playerScore;
	_players.push_back(player);
	std::sort(_players.begin(), _players.end(), sortFunction);
	_gamePlayersDatabaseSerializer->saveDatabaseData(_players);
}

bool sortFunction(const DatabaseInformation &left, const DatabaseInformation &right)
{
	return (left.playerScore > right.playerScore);
}