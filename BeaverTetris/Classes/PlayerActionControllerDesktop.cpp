#include "PlayerActionControllerDesktop.h"
#include "PlayerGameControlsDataSource.h"
#include "GameViewStyleHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"

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

map<EventKeyboard::KeyCode, Node*> PlayerActionControllerDesktop::makeControllersViews()
{
	map<EventKeyboard::KeyCode, Node*> controllersViews;

	int controllersCount = _playerGameControlsDataSource->getPlayerControlsCount();

	for (int controllerIndex = 0; controllerIndex < controllersCount; controllerIndex++)
	{
		Sprite *playerControllerView = Sprite::create("HelloWorld.png");
	    playerControllerView->setScaleY(0.06f);
		playerControllerView->setScaleX(0.04f);
		playerControllerView->setColor(Color3B::GREEN);
		Vec2 viewPosition = _playerGameControlsDataSource->getPlayerControlPositionOnIndex(controllerIndex);
		playerControllerView->setPosition(viewPosition);
		playerControllerView->setTag(controllerIndex);

		EventKeyboard::KeyCode keyCode = (EventKeyboard::KeyCode) _playerGameControlsDataSource->getPlayerControlKeyboardKeyOnIndex(controllerIndex);
		controllersViews[keyCode] = playerControllerView;
	}

	return controllersViews;
}

void PlayerActionControllerDesktop::addViewsToController(map<EventKeyboard::KeyCode, Node*> aViews)
{
	map<EventKeyboard::KeyCode, Node*>::iterator viewsIterator;
	for (viewsIterator = aViews.begin(); viewsIterator != aViews.end(); viewsIterator++)
	{
		Node* controllerView = viewsIterator->second;
		this->addChild(controllerView);
	}
}

void PlayerActionControllerDesktop::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	map<EventKeyboard::KeyCode, Node*>::iterator viewsIterator; 
	viewsIterator = _controllersViews.find(aKeyCode);
	if (viewsIterator != _controllersViews.end() && _gameTimeStepController->getUpdataAvailable() == true)
	{
		Node* controllerView = _controllersViews[aKeyCode];
		int controllerViewIndex = controllerView->getTag();
		function<void()> callback = _playerGameControlsDataSource->getPlayerControlCallbackForIndex(controllerViewIndex);
		GameViewStyleHelper::runStandardButtonActionWithCallback(controllerView ,callback);
	}
}