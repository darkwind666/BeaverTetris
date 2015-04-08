#include "StartGameMenuController.h"
#include "StartGameMenuDataSource.h"
#include "GameViewStyleHelper.h"

using namespace cocos2d;

StartGameMenuController::StartGameMenuController(void)
{
	_startGameViewDataSource = new StartGameMenuDataSource();
	createStartMenu();
}


StartGameMenuController::~StartGameMenuController(void)
{
}

void StartGameMenuController::createStartMenu()
{
	Menu *startGameMenu = Menu::create();
	startGameMenu->setPosition(Vec2(0,0));

	int menuItemsCount = _startGameViewDataSource->getMenuItemsCount();

	for (int itemIndex = 0; itemIndex < menuItemsCount; itemIndex++)
	{
		MenuItemImage *menuItem = MenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(StartGameMenuController::buttonWasPressed, this));
		menuItem->setScaleX(0.2f);
		menuItem->setScaleY(0.07f);
		menuItem->setTag(itemIndex);
		menuItem->setPosition(_startGameViewDataSource->getMenuItemPositionForIndex(itemIndex));
		startGameMenu->addChild(menuItem);
		
	}
	this->addChild(startGameMenu);
}

void StartGameMenuController::buttonWasPressed(Object* pSender)
{
	Node *button = (Node*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = _startGameViewDataSource->getMenuItemCallbackForIndex(buttonTag);
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}