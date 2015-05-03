#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class GameTimeStepController;
class EventListenerKeyboard;
class MainGamePauseDelegate;
class GameWorldController;

class MainGamePausePopUp : public cocos2d::Node,  public ScreenPopUp
{
public:
	MainGamePausePopUp(GameWorldController *aGameWorldController);
	~MainGamePausePopUp(void);

	virtual void showPopUp();

private:

	cocos2d::Node* _popUpView;
	GameTimeStepController *_gameTimeStepController;
	cocos2d::EventListenerKeyboard *_eventListenerKeyboard;
	MainGamePauseDelegate *_mainGamePauseDelegate;
	GameWorldController *_gameWorldController;
	
	void setUpKeyboard();
	cocos2d::Node* makePopUpView();
	cocos2d::Node* getPopUpMenu();
	void closePopUp(cocos2d::Object* pSender);
	void goToSelectLevelScreen(cocos2d::Object* pSender);
	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);
	void hidePopUp();

};

