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
	void savePlayer(PlayerInformation aPlayer);
	void cleanSavedPlayer();

private:

	cocos2d::FileUtils *_fileUtils;
	PlayerInformation _savedPlayer;

	void createFile();

};

