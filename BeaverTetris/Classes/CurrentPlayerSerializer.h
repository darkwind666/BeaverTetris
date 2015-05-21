#pragma once

#include "GameStructures.h"
#include "cocos2d.h"
#include <string>
#include <vector>

class CurrentPlayerSerializer
{
public:
	CurrentPlayerSerializer(void);
	~CurrentPlayerSerializer(void);

	bool availablePlayer();
	PlayerInformation getSavedPlayer();
	void savePlayer(PlayerInformation aPlayer);
	void cleanSavedPlayer();

private:

	cocos2d::FileUtils *_fileUtils;

	void createFile();
	std::map<std::string, LevelSpellInformation> getSpellsInformationFromData(cocos2d::ValueMap &aData);
	std::vector<std::string> getCompletedTutorialsInformationFromData(cocos2d::ValueMap &aData);
	cocos2d::ValueMap getSpellsDataFromPlayer(PlayerInformation &aPlayer);
	cocos2d::ValueVector getTutorialsDataFromPlayer(PlayerInformation &aPlayer);

};

