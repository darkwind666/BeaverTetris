#include "GamePlayersDatabase.h"

using namespace std;
bool sortFunction(const PlayerInformation &left, const PlayerInformation &right);

GamePlayersDatabase::GamePlayersDatabase(void)
{
	_players = vector <PlayerInformation>();
}


GamePlayersDatabase::~GamePlayersDatabase(void)
{
}


int GamePlayersDatabase::getPlayersCount()
{
	return _players.size();
}

string GamePlayersDatabase::getPlayerNameForIndex(int aIndex)
{
	PlayerInformation player = _players[aIndex];
	return player.playerName;
}

int GamePlayersDatabase::getPlayerScoreForIndex(int aIndex)
{
	PlayerInformation player = _players[aIndex];
	return player.playerScore;
}



void GamePlayersDatabase::setPlayerResult(std::string aPlayerName, int playerScore)
{
	PlayerInformation player;
	player.playerName = aPlayerName;
	player.playerScore = playerScore;
	_players.push_back(player);
}

void GamePlayersDatabase::sortPlayers()
{
	sort(_players.begin, _players.end, sortFunction);
}

bool sortFunction(const PlayerInformation &left, const PlayerInformation &right)
{
	return (left.playerScore > right.playerScore);
}