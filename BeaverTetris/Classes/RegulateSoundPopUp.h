#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class RegulateSoundPopUp : public cocos2d::Node,  public ScreenPopUp
{
public:
	RegulateSoundPopUp(void);
	~RegulateSoundPopUp(void);

	virtual void showPopUp();

private:

	cocos2d::Vec2 _oldControllerPosition;
	cocos2d::Node* _popUpView;

	cocos2d::Node* makePopUpView();
	void closePopUp(cocos2d::Object* pSender);
};

