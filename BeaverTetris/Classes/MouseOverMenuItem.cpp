#include "MouseOverMenuItem.h"

using namespace cocos2d;

MouseOverMenuItem::MouseOverMenuItem(std::string activeImageKey, std::string inactiveImageKey, ccMenuCallback callback)
{
	Sprite *normalView = Sprite::createWithSpriteFrameName(inactiveImageKey);
	Sprite *selectedView = Sprite::createWithSpriteFrameName(activeImageKey);
	MenuItemSprite *menuItem = MenuItemSprite::create(normalView, selectedView, callback);
	_menuItem = menuItem;
	Menu *menuItemMenu = Menu::create();
	menuItemMenu->setPosition(Vec2(0.0f, 0.0f));
	menuItemMenu->addChild(menuItem);
	this->addChild(menuItemMenu);

	//setMouseListner();
}


MouseOverMenuItem::~MouseOverMenuItem(void)
{
	//_eventDispatcher->removeEventListener(_mouseListner);
}

void MouseOverMenuItem::setMouseListner()
{
	/*
	_mouseListner = EventListenerMouse::create();
	_mouseListner->onMouseMove = CC_CALLBACK_1(MouseOverMenuItem::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListner, this);
	*/
}

void MouseOverMenuItem::onMouseMove(Event *aEvent)
{
	/*
	EventMouse *mouseEvent = (EventMouse*)aEvent;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 mouseLocation = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY() + visibleSize.height);
	changeMenuItemImageWithMouseLocation(mouseLocation);
	*/
}

void MouseOverMenuItem::changeMenuItemImageWithMouseLocation(cocos2d::Vec2 aMouseLocation)
{
	Vec2 locationInNode = _menuItem->convertToNodeSpace(aMouseLocation);
	Rect menuItemRect = Rect(0, 0, _menuItem->getContentSize().width, _menuItem->getContentSize().height);
	if (menuItemRect.containsPoint(locationInNode))
	{
		_menuItem->selected();
	}
	else
	{
		_menuItem->unselected();
	}
}

void MouseOverMenuItem::setTag(int tag)
{
	MenuItem::setTag(tag);
	_menuItem->setTag(tag);
}
