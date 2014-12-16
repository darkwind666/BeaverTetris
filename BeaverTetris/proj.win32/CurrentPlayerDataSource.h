#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GamePlayersDatabase.h"
#include "GameStructures.h"

class CurrentPlayerDataSource :public ServiceInterface
{
public:
	CurrentPlayerDataSource(GamePlayersDatabase *aGamePlayersDatabase);
	~CurrentPlayerDataSource();

	bool isThereCurentPlayer();
	std::string getPlayerName();
	int getPlayerScore();
	int getPlayerCompletedLevelsCount();
	int getPlayerAvailableSpellsCount();

	void setNewPlayerWithName(std::string aNewPlayerName);
	void setPlayerScore(int aPlayerScore);
	void completeLevel(std::string aCompletedLevelName);

	void sendPlayerResultToDatabase();
	void cleanPlayer();

private:
	std::vector <std::string> _completedLevelsNames;
	GamePlayersDatabase *_gamePlayersDatabase;
	bool _isThereCurentPlayer;
	PlayerInformation _playerData;
};
