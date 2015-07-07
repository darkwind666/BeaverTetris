#pragma once

#include "GameStructures.h"
#include <vector>
#include "cocos2d.h"

class GamePlayersDatabaseSerializer
{
public:
	GamePlayersDatabaseSerializer(void);
	~GamePlayersDatabaseSerializer(void);

	std::vector<DatabaseInformation> getDatabaseData();
	void saveDatabaseData(std::vector<DatabaseInformation> &aPlayers);

private:

	cocos2d::FileUtils *_fileUtils;
	std::string _fullWritablePath;

	void createFile();
	void fillDatabaseWithPlayers(std::vector<DatabaseInformation> &aDatabaseData, cocos2d::ValueVector &aPlayers);
	cocos2d::ValueVector getPlayersInformationFromPlayers(std::vector<DatabaseInformation> &aPlayers);

};

