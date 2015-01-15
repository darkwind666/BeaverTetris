#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class RegulateSoundPopUp : public cocos2d::CCNode,  public ScreenPopUp
{
public:
	RegulateSoundPopUp(void);
	~RegulateSoundPopUp(void);

	virtual void showPopUp();

private:

	cocos2d::Vec2 _oldControllerPosition;
	cocos2d::CCNode* _popUpView;

	cocos2d::CCNode* makePopUpView();
	void closePopUp(cocos2d::CCObject* pSender);
};

