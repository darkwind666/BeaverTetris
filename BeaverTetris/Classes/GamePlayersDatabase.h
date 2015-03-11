#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GameStructures.h"

class GamePlayersDatabase : public ServiceInterface
{
public:

	GamePlayersDatabase(void);
	~GamePlayersDatabase(void);

	int getPlayersCount();
	std::string getPlayerNameForIndex(int aIndex);
	int getPlayerScoreForIndex(int aIndex);

	void setPlayerResult(std::string aPlayerName, int playerScore);

	void sortPlayers();

private:

	std::vector <PlayerInformation> _players;

};

