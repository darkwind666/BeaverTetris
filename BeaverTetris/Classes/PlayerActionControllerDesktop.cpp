#include "PlayerActionControllerDesktop.h"
#include "PlayerGameControlsDataSource.h"
#include "GameViewStyleHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "GameAnimationActionsConstants.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;
using namespace std;

PlayerActionControllerDesktop::PlayerActionControllerDesktop(void)
{
	_playerGameControlsDataSource = new PlayerGameControlsDataSource();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	setUpKeyboard();
	_controllersViews = makeControllersViews();
	addViewsToController(_controllersViews);
}


PlayerActionControllerDesktop::~PlayerActionControllerDesktop(void)
{
}

void PlayerActionControllerDesktop::setUpKeyboard()
{
	EventListenerKeyboard *keyboardListner = EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(PlayerActionControllerDesktop::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
}

map<EventKeyboard::KeyCode, MenuItem*> PlayerActionControllerDesktop::makeControllersViews()
{
	map<EventKeyboard::KeyCode, MenuItem*> controllersViews;
	int controllersCount = _playerGameControlsDataSource->getPlayerControlsCount();
	for (int controllerIndex = 0; controllerIndex < controllersCount; controllerIndex++)
	{
		EventKeyboard::KeyCode keyCode = (EventKeyboard::KeyCode) _playerGameControlsDataSource->getPlayerControlKeyboardKeyOnIndex(controllerIndex);
		MenuItem *playerControllerView = getPlayerControlViewWithKey(keyCode);
		Vec2 viewPosition = _playerGameControlsDataSource->getPlayerControlPositionOnIndex(controllerIndex);
		playerControllerView->setPosition(viewPosition);
		float controllRotation = _playerGameControlsDataSource->getPlayerControlRotationForIndex(controllerIndex);
		playerControllerView->setRotation(controllRotation);
		playerControllerView->setTag(controllerIndex);
		controllersViews[keyCode] = playerControllerView;
	}
	return controllersViews;
}

MenuItem* PlayerActionControllerDesktop::getPlayerControlViewWithKey(EventKeyboard::KeyCode aKey)
{
	Sprite *playerControllerInactiveImage = CocosNodesHelper::getSpriteWithKey(playerControlActiveImageKey);
	Sprite *playerControllerActiveImage = CocosNodesHelper::getSpriteWithKey(playerControlActiveImageKey);
	MenuItemSprite *playerControllerView = MenuItemSprite::create(playerControllerInactiveImage, playerControllerActiveImage, [this, aKey](Ref* target){activatePlayerControllerOnKeyCode(aKey);});
	return playerControllerView;
}

void PlayerActionControllerDesktop::addViewsToController(map<EventKeyboard::KeyCode, MenuItem*> aViews)
{
	Menu *playerControlsMenu = Menu::create();
	playerControlsMenu->setPosition(Vec2(0, 0));
	map<EventKeyboard::KeyCode, MenuItem*>::iterator viewsIterator;
	for (viewsIterator = aViews.begin(); viewsIterator != aViews.end(); viewsIterator++)
	{
		MenuItem* controllerView = viewsIterator->second;
		playerControlsMenu->addChild(controllerView);
	}
	this->addChild(playerControlsMenu);
}

void PlayerActionControllerDesktop::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	map<EventKeyboard::KeyCode, MenuItem*>::iterator viewsIterator; 
	viewsIterator = _controllersViews.find(aKeyCode);
	if (viewsIterator != _controllersViews.end())
	{
		activatePlayerControllerOnKeyCode(aKeyCode);
	}
}

void PlayerActionControllerDesktop::activatePlayerControllerOnKeyCode(cocos2d::EventKeyboard::KeyCode aKeyCode)
{
	if (_gameTimeStepController->getUpdataAvailable() == true)
	{
		_gameTimeStepController->setUpdateAvailable(false);
		MenuItem* controllerView = _controllersViews[aKeyCode];
		int controllerViewIndex = controllerView->getTag();
		function<void()> callback = getCallbackWithButtonIndex(controllerViewIndex);
		GameViewStyleHelper::runButtonActionWithCallbackAndDuration(controllerView ,callback, gameControllButtonActionDuration);
	}
}

function<void()> PlayerActionControllerDesktop::getCallbackWithButtonIndex(int aButtonIndex)
{
	function<void()> callback = [this, aButtonIndex](){
		_gameTimeStepController->setUpdateAvailable(true);
		function<void()> buttonCallback = _playerGameControlsDataSource->getPlayerControlCallbackForIndex(aButtonIndex);
		buttonCallback();
	};
	return callback;
}