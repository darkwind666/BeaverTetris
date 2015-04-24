#pragma once

#include "cocos2d.h"
#include <string>

class MouseOverMenuItem : public cocos2d::MenuItem
{
public:
	MouseOverMenuItem(std::string activeImageKey, std::string inactiveImageKey, cocos2d::ccMenuCallback callback);
	~MouseOverMenuItem(void);

	virtual void setTag(int tag);

private:

	MenuItem *_menuItem;
	cocos2d::EventListenerMouse *_mouseListner;

	void setMouseListner();
	void onMouseMove(cocos2d::Event *aEvent);
	void changeMenuItemImageWithMouseLocation(cocos2d::Vec2 aMouseLocation);

};

