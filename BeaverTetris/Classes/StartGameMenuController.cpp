#include "StartGameMenuController.h"
#include "StartGameMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "MouseOverMenuItem.h"

using namespace cocos2d;
using namespace std;

StartGameMenuController::StartGameMenuController(void)
{
	_startGameViewDataSource = new StartGameMenuDataSource();
	_menuItems = getMenuItems();
	makeStartMenuView();
}


StartGameMenuController::~StartGameMenuController(void)
{
}

vector<Node*> StartGameMenuController::getMenuItems()
{
	vector<Node*> menuItems;
	int menuItemsCount = _startGameViewDataSource->getMenuItemsCount();
	for (int itemIndex = 0; itemIndex < menuItemsCount; itemIndex++)
	{
		string unselectedImageName = _startGameViewDataSource->getMenuInactiveImageForIndex(itemIndex);
		string selectedImageName = _startGameViewDataSource->getMenuActiveImageForIndex(itemIndex);
		MouseOverMenuItem *menuItem = new MouseOverMenuItem(selectedImageName, unselectedImageName, CC_CALLBACK_1(StartGameMenuController::buttonWasPressed, this));
		Node *buttonText = getButtonTextForIndex(itemIndex);
		menuItem->addChild(buttonText);
		float buttonRotation = _startGameViewDataSource->getButtonRotationForIndex(itemIndex);
		menuItem->setRotation(buttonRotation);
		menuItem->setTag(itemIndex);
		menuItem->setPosition(_startGameViewDataSource->getMenuItemPositionForIndex(itemIndex));
		menuItems.push_back(menuItem);
	}
	return menuItems;
}

Node* StartGameMenuController::getButtonTextForIndex(int aIndex)
{
	int textSize = _startGameViewDataSource->getTextSizeForIndex(aIndex);
	Label *buttonText = GameViewStyleHelper::getStandardLabelWithFontSize(textSize);
	Vec2 buttonPosition = _startGameViewDataSource->getButtonTextPositionForIndex(aIndex);
	buttonText->setPosition(buttonPosition);
	float buttonTextRotation = _startGameViewDataSource->getButtonTextRotationForIndex(aIndex);
	buttonText->setRotation(buttonTextRotation);
	string text = _startGameViewDataSource->getButtonTextForIndex(aIndex);
	buttonText->setString(text);
	return buttonText;
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

void StartGameMenuController::buttonWasPressed(Object* pSender)
{
	Node *button = (Node*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = _startGameViewDataSource->getMenuItemCallbackForIndex(buttonTag);
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}