#pragma once

#include "cocos2d.h"

class GamePlayersDatabase;

class GamesRecordsBoardController : public cocos2d::Node
{
public:
	GamesRecordsBoardController(void);
	~GamesRecordsBoardController(void);

private:

	GamePlayersDatabase *_gamePlayersDatabase;

	void makeBoardView();
	int getRecordsCount();
	cocos2d::Node* getRecordPadWithIndex(int aIndex);
	cocos2d::Node* getPlayerNameLabelWithIndex(int aIndex);
	cocos2d::Node* getPlayerScoreLabelWithIndex(int aIndex);

};

