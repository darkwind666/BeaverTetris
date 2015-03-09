#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class GameTimeStepController;
class EventListenerKeyboard;
class MainGamePauseDelegate;
class GameWorldController;

class MainGamePausePopUp : public cocos2d::CCNode,  public ScreenPopUp
{
public:
	MainGamePausePopUp(GameWorldController *aGameWorldController);
	~MainGamePausePopUp(void);

	virtual void showPopUp();

private:

	cocos2d::Vec2 _oldControllerPosition;
	cocos2d::CCNode* _popUpView;
	GameTimeStepController *_gameTimeStepController;
	cocos2d::EventListenerKeyboard *_eventListenerKeyboard;
	MainGamePauseDelegate *_mainGamePauseDelegate;
	GameWorldController *_gameWorldController;
	
	void setUpKeyboard();
	cocos2d::CCNode* makePopUpView();
	void closePopUp(cocos2d::CCObject* pSender);
	void goToSelectLevelScreen(cocos2d::CCObject* pSender);
	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);
	void hidePopUp();

};

