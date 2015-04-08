#include "RegulateSoundPopUp.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameSoundEffectsRegulator.h"
#include "GameBackgroundSoundRegulator.h"
#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

RegulateSoundPopUp::RegulateSoundPopUp(void)
{
	ScreenPopUp::subscribePopUpToMessage(this, kRegulateSoundPopUp);
	_popUpView = makePopUpView();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_popUpView,this,startGameRegulateSoundPadKey);
}


RegulateSoundPopUp::~RegulateSoundPopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kRegulateSoundPopUp);
}

void RegulateSoundPopUp::showPopUp()
{
	_oldControllerPosition = _popUpView->getPosition();
	Vec2 newControllerPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameRegulateSoundPadKey);
	ActionInterval *moveController = CCMoveTo::create(regulateSoundPopUpStartAppearDuration, newControllerPosition);
	Action *ease = CCEaseBackOut::create(moveController);
	_popUpView->runAction(ease);
}

Node* RegulateSoundPopUp::makePopUpView()
{

	LayerColor *popUpPad = LayerColor::create(Color4B::RED, 300, 200);
	popUpPad->ignoreAnchorPointForPosition(false);

	GameSoundEffectsRegulator *soundEffectsRegulator = new GameSoundEffectsRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(soundEffectsRegulator,popUpPad,startGameRegulateSoundEffectsSliderKey);

	GameBackgroundSoundRegulator *backgroundSoundRegulator = new GameBackgroundSoundRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundSoundRegulator,popUpPad,startGameRegulateSoundSliderKey);

	MenuItemImage *closeButtonItem = MenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(RegulateSoundPopUp::closePopUp, this));
	closeButtonItem->setScaleX(0.2f);
	closeButtonItem->setScaleY(0.07f);
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButtonItem,popUpPad,startGameRegulateSoundCloseButtonKey);

	return popUpPad;

}

void RegulateSoundPopUp::closePopUp(Object* pSender)
{
	Node *button = (Node*)pSender;
	std::function<void()> buttonCallback = [this](){
		ActionInterval *moveController = CCMoveTo::create(regulateSoundPopUpStartDisapperDuration, _oldControllerPosition);
		_popUpView->runAction(moveController);
	};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}