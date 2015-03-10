#pragma once

#include "ScreenPopUp.h"
#include "cocos2d.h"

class MainGameEndPopUp : public cocos2d::CCNode,  public ScreenPopUp
{
public:
	MainGameEndPopUp(void);
	~MainGameEndPopUp(void);

	virtual void showPopUp();

private:

	cocos2d::CCNode* _popUpView;

	cocos2d::CCNode* makePopUpView();
	void fillViewWithElements();
	cocos2d::Vec2 getElementPositionForIndex(int aIndex);

};

