#include "RegulateSoundPopUp.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameSoundEffectsRegulator.h"
#include "GameBackgroundSoundRegulator.h"
#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameAnalyticController.h"

using namespace cocos2d;

RegulateSoundPopUp::RegulateSoundPopUp(void)
{
	ScreenPopUp::subscribePopUpToMessage(this, kRegulateSoundPopUp);
	_popUpView = makePopUpView();
	_popUpView->setVisible(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_popUpView,this,startGameRegulateSoundBackgroundKey);
	_listner = getListner();
}


RegulateSoundPopUp::~RegulateSoundPopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kRegulateSoundPopUp);
	_eventDispatcher->removeEventListener(_listner);
}

Node* RegulateSoundPopUp::makePopUpView()
{
	Node *popUpBackground = GameViewStyleHelper::getPopUpBackground();
	Node *popUpMenu = getPopUpMenu();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(popUpMenu,popUpBackground,startGameRegulateSoundPadKey);
	return popUpBackground;
}

Node* RegulateSoundPopUp::getPopUpMenu()
{
	Sprite *popUpPad = CocosNodesHelper::getSpriteWithKey(startGameRegulateSoundPadKey);

	GameSoundEffectsRegulator *soundEffectsRegulator = new GameSoundEffectsRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(soundEffectsRegulator,popUpPad,startGameRegulateSoundEffectsSliderKey);

	GameBackgroundSoundRegulator *backgroundSoundRegulator = new GameBackgroundSoundRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundSoundRegulator,popUpPad,startGameRegulateSoundSliderKey);

	GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallback(popUpPad, startGameRegulateSoundCloseButtonKey, CC_CALLBACK_1(RegulateSoundPopUp::closePopUp, this));

	return popUpPad;
}

EventListenerTouchOneByOne* RegulateSoundPopUp::getListner()
{
	EventListenerTouchOneByOne *listner = EventListenerTouchOneByOne::create();
	listner->setSwallowTouches(false);
	listner->onTouchBegan = [](Touch *touch, Event *aEvent){return true;};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);
	return listner;
}

void RegulateSoundPopUp::showPopUp()
{
	_popUpView->setVisible(true);
	_listner->setSwallowTouches(true);
	GameAnalyticController *gameAnalyticController = (GameAnalyticController*)ServiceLocator::getServiceForKey(gameAnalyticControllerKey);
	gameAnalyticController->goToPopUp(kRegulateSoundPopUp);
}

void RegulateSoundPopUp::closePopUp(Object* pSender)
{
	Node *button = (Node*)pSender;
	std::function<void()> buttonCallback = [this](){
		_popUpView->setVisible(false);
		_listner->setSwallowTouches(false);
	};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}