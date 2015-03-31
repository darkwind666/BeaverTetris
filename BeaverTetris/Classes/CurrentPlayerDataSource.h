#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GameStructures.h"

class CurrentPlayerSerializer;
class GameLevelsDataSource;

class CurrentPlayerDataSource :public ServiceInterface
{
public:
	CurrentPlayerDataSource(GameLevelsDataSource *aGameLevelsDataSource);
	~CurrentPlayerDataSource();

	bool isThereCurentPlayer();
	std::string getPlayerName();
	int getPlayerScore();
	int getPlayerCompletedLevelsCount();
	int getPlayerAvailableSpellsCount();
	int getSelectedGameLevelIndex();
	int getSpellCountForKey(std::string aKey);

	void setNewPlayerWithName(std::string aNewPlayerName);
	void setPlayerScore(int aPlayerScore);
	void completeLevel(std::string aCompletedLevelName);
	void setSelectedGameLevelIndex(int aGameLevelIndex);
	void setNewSpellCountForKey(int spellCount, std::string aKey);

	void savePlayer();
	void cleanPlayer();

private:

	std::vector <std::string> _completedLevelsNames;
	bool _isThereCurentPlayer;
	PlayerInformation _playerData;
	int _selectedGameLevelIndex;
	CurrentPlayerSerializer *_currentPlayerSerializer;
	GameLevelsDataSource *_gameLevelsDataSource;

	void setUpPlayer();
	void fillCompletedLevelsNames();

};

