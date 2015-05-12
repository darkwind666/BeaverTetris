#pragma once

#include "cocos2d.h"
#include "GameEnums.h"
#include <map>
#include <functional>

class BackButtonController : public cocos2d::Node
{
public:
	BackButtonController(GameState screenType);
	~BackButtonController(void);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *aEvent);

private:

	GameState _screenType;
	std::map< GameState, std::function<void()> > _backButtonHandlers;

	void setUpKeyboard();
	std::map< GameState, std::function<void()> > getBackButtonHandlers();
	void backButtonInMainGamePressed();
	void restorePlayer();
	void gameEndedBackButtonPressed();
	void gameEndedWithWinResult();

};

