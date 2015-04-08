#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class GameWorldController;
class GameHudsController;
class MainGameEndPopUpSoundController;

class MainGameEndPopUp : public cocos2d::Node,  public ScreenPopUp
{
public:
	MainGameEndPopUp(GameWorldController *aGameWorldController, GameHudsController *aGameHudsController);
	~MainGameEndPopUp(void);

	virtual void showPopUp();
	virtual void onExitTransitionDidStart();

private:

	cocos2d::Node* _popUpView;
	GameWorldController *_gameWorldController;
	GameHudsController *_gameHudsController;
	MainGameEndPopUpSoundController *_mainGameEndPopUpSoundController;

	cocos2d::Node* makePopUpView();
	void fillViewWithElements();
	cocos2d::Vec2 getElementPositionForIndex(int aIndex);

};

