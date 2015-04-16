#include "StartGameMenuController.h"
#include "StartGameMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;
using namespace std;

StartGameMenuController::StartGameMenuController(void)
{
	_startGameViewDataSource = new StartGameMenuDataSource();
	setMouseListner();
	_menuItems = getMenuItems();
	makeStartMenuView();
}


StartGameMenuController::~StartGameMenuController(void)
{
}

void StartGameMenuController::setMouseListner()
{
	EventListenerMouse *mouseListner = EventListenerMouse::create();
	mouseListner->onMouseMove = CC_CALLBACK_1(StartGameMenuController::onMouseMove, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}

vector<Node*> StartGameMenuController::getMenuItems()
{
	vector<Node*> menuItems;
	int menuItemsCount = _startGameViewDataSource->getMenuItemsCount();
	for (int itemIndex = 0; itemIndex < menuItemsCount; itemIndex++)
	{
		string unselectedImageName = _startGameViewDataSource->getMenuInactiveImageForIndex(itemIndex);
		string selectedImageName = _startGameViewDataSource->getMenuActiveImageForIndex(itemIndex);
		Sprite *normalView = Sprite::createWithSpriteFrameName(unselectedImageName);
		Sprite *selectedView = Sprite::createWithSpriteFrameName(selectedImageName);
		MenuItemSprite *menuItem = MenuItemSprite::create(normalView, selectedView, CC_CALLBACK_1(StartGameMenuController::buttonWasPressed, this));
		menuItem->setScale(0.9f);
		menuItem->setTag(itemIndex);
		menuItem->setPosition(_startGameViewDataSource->getMenuItemPositionForIndex(itemIndex));
		menuItems.push_back(menuItem);
	}
	return menuItems;
}

void StartGameMenuController::makeStartMenuView()
{
	Sprite *staircase = CocosNodesHelper::getSpriteWithKey(startGameMenuKey);
	this->addChild(staircase);
	createStartMenu();
}

void StartGameMenuController::createStartMenu()
{
	Menu *startGameMenu = Menu::create();
	startGameMenu->setPosition(Vec2(0,0));
	vector<Node*>::iterator menuItemsIterator;
	for (menuItemsIterator = _menuItems.begin(); menuItemsIterator != _menuItems.end(); menuItemsIterator++)
	{
		Node *menuItem = *menuItemsIterator;
		startGameMenu->addChild(menuItem);
	}
	this->addChild(startGameMenu);
}

void StartGameMenuController::onMouseMove(Event *aEvent)
{
	EventMouse *mouseEvent = (EventMouse*)aEvent;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 mouseLocation = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY() + visibleSize.height);
	configurateMenuItemsWithMouseLocation(mouseLocation);
}

void StartGameMenuController::configurateMenuItemsWithMouseLocation(Vec2 aMouseLocation)
{
	vector<Node*>::iterator menuItemsIterator;
	for (menuItemsIterator = _menuItems.begin(); menuItemsIterator != _menuItems.end(); menuItemsIterator++)
	{
		MenuItem *menuItem = (MenuItem*)*menuItemsIterator;
		changeMenuItemImageWithMouseLocation(menuItem, aMouseLocation);
	}
}

void StartGameMenuController::changeMenuItemImageWithMouseLocation(MenuItem *aMenuItem, Vec2 aMouseLocation)
{
	Vec2 locationInNode = aMenuItem->convertToNodeSpace(aMouseLocation);
	Rect menuItemRect = Rect(0, 0, aMenuItem->getContentSize().width, aMenuItem->getContentSize().height);
	if (menuItemRect.containsPoint(locationInNode))
	{
		aMenuItem->selected();
	}
	else
	{
		aMenuItem->unselected();
	}
}

void StartGameMenuController::buttonWasPressed(Object* pSender)
{
	Node *button = (Node*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = _startGameViewDataSource->getMenuItemCallbackForIndex(buttonTag);
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}