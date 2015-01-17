#pragma once

#include "cocos2d.h"

class PlayerStatusDataSource;

class SelectLevelPlayerStatusController : public cocos2d::Node
{
public:
	SelectLevelPlayerStatusController(void);
	~SelectLevelPlayerStatusController(void);

	virtual void onEnterTransitionDidFinish();

private:

	PlayerStatusDataSource *_playerStatusDataSource;
	cocos2d::Node* _playerStatusView;
	cocos2d::LabelTTF* _playerName;
	cocos2d::LabelTTF* _playerScore;

	cocos2d::LabelTTF* getStandardLabel();
	cocos2d::Node* getPlayerStatusPad();
	void placeAllViewParts();

};

