#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GameStructures.h"

class GamePlayersDatabaseSerializer;

class GamePlayersDatabase : public ServiceInterface
{
public:

	GamePlayersDatabase(void);
	~GamePlayersDatabase(void);

	int getPlayersCount();
	std::string getPlayerNameForIndex(int aIndex);
	int getPlayerScoreForIndex(int aIndex);

	void setPlayerResult(std::string aPlayerName, int playerScore);

private:

	GamePlayersDatabaseSerializer *_gamePlayersDatabaseSerializer;
	std::vector <DatabaseInformation> _players;

};

