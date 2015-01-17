#pragma once

#include "PlayerStatusDelegateInterface.h"
#include "cocos2d.h"

class PlayerStatusDataSource;

class SelectLevelPlayerStatusController : public cocos2d::Node, public PlayerStatusDelegateInterface
{
public:
	SelectLevelPlayerStatusController(void);
	~SelectLevelPlayerStatusController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void showPlayerStatus();

	void setDelegate(PlayerStatusDelegateInterface *aDelegate);

private:

	PlayerStatusDataSource *_playerStatusDataSource;
	cocos2d::Node* _playerStatusView;
	cocos2d::LabelTTF* _playerName;
	cocos2d::LabelTTF* _playerScore;
	PlayerStatusDelegateInterface *_delegate;

	cocos2d::LabelTTF* getStandardLabel();
	cocos2d::Node* getPlayerStatusPad();
	void placeAllViewParts();

	cocos2d::Action* getShowControllerAnimation();
	cocos2d::FiniteTimeAction* getCallback();

};

