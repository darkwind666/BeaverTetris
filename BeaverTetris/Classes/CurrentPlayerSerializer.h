#pragma once

#include "GameStructures.h"
#include "cocos2d.h"

class CurrentPlayerSerializer
{
public:
	CurrentPlayerSerializer(void);
	~CurrentPlayerSerializer(void);

	bool availablePlayer();
	PlayerInformation getSavedPlayer();
	std::map<std::string, int> getSpellsInformationFromData(cocos2d::ValueMap &aData);
	void savePlayer(PlayerInformation aPlayer);
	cocos2d::ValueMap getSpellsDataFromPlayer(PlayerInformation &aPlayer);
	void cleanSavedPlayer();

private:

	cocos2d::FileUtils *_fileUtils;

	void createFile();

};

