#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class RegulateSoundPopUp : public cocos2d::Layer,  public ScreenPopUp
{
public:
	RegulateSoundPopUp(void);
	~RegulateSoundPopUp(void);

	virtual void showPopUp();

private:

	cocos2d::Vec2 _oldControllerPosition;
	cocos2d::Node* _popUpView;
	cocos2d::EventListenerTouchOneByOne *_listner;

	cocos2d::Node* makePopUpView();
	cocos2d::Node* getPopUpMenu();
	cocos2d::EventListenerTouchOneByOne* getListner();
	void closePopUp(cocos2d::Object* pSender);
};

