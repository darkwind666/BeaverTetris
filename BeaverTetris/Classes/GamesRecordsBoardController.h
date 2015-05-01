#pragma once

#include "cocos2d.h"
#include <string>

class GamePlayersDatabase;

class GamesRecordsBoardController : public cocos2d::Node
{
public:
	GamesRecordsBoardController(void);
	~GamesRecordsBoardController(void);

private:

	GamePlayersDatabase *_gamePlayersDatabase;

	void makeBoardView();
	void createRecordsBoard();
	int getRecordsCount();
	cocos2d::Node* getRecordPadWithIndex(int aIndex);
	std::string getRecordPadImageNameWithIndex(int aIndex);
	cocos2d::Node* getPlayerNameLabelWithIndex(int aIndex);
	float getLabelFontSizeWithIndex(int aIndex);
	void createBackToMainMenuButton();
	cocos2d::MenuItem* getCloseButton();

};

