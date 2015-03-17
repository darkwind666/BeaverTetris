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

	void setNewPlayerWithName(std::string aNewPlayerName);
	void setPlayerScore(int aPlayerScore);
	void completeLevel(std::string aCompletedLevelName);
	void setSelectedGameLevelIndex(int aGameLevelIndex);
	void setNewSpellForKey(std::string aKey);

	void savePlayer();
	void cleanPlayer();

private:

	std::vector <std::string> _completedLevelsNames;
	std::vector <std::string> _availableSpellsNames;
	std::vector <std::string> _allSpellsNames;
	bool _isThereCurentPlayer;
	PlayerInformation _playerData;
	int _selectedGameLevelIndex;
	CurrentPlayerSerializer *_currentPlayerSerializer;
	GameLevelsDataSource *_gameLevelsDataSource;

	std::vector <std::string> getAllSpellsNames();
	void setUpPlayer();
	void fillCompletedLevelsNames();
	void fillAvailableSpells();

};

