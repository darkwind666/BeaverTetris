#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class GameWorldController;
class GameHudsController;

class MainGameEndPopUp : public cocos2d::CCNode,  public ScreenPopUp
{
public:
	MainGameEndPopUp(GameWorldController *aGameWorldController, GameHudsController *aGameHudsController);
	~MainGameEndPopUp(void);

	virtual void showPopUp();

private:

	cocos2d::CCNode* _popUpView;
	GameWorldController *_gameWorldController;
	GameHudsController *_gameHudsController;

	cocos2d::CCNode* makePopUpView();
	void fillViewWithElements();
	cocos2d::Vec2 getElementPositionForIndex(int aIndex);

};

