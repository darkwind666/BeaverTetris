#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GamePlayersDatabase.h"

class CurrentPlayerDataSource :public ServiceInterface
{
public:
	CurrentPlayerDataSource(GamePlayersDatabase *aGamePlayersDatabase);
	~CurrentPlayerDataSource(void);

	bool isThereCurentPlayer();
	std::string getPlayerName();
	int getPlayerScore();
	int getPlayerCompletedLevels();

	void setNewPlayerWithName(std::string);
	void setPlayerScore(int aPlayerScore);
	void completeLevel(std::string aCompletedLevelName);

	void sendPlayerResultToDatabase();
	void cleanPlayer();

private:

	std::vector <std::string> _completedLevelsNames;
	GamePlayersDatabase *_gamePlayersDatabase;

};

