#include "RegulateSoundPopUp.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameSoundEffectsRegulator.h"
#include "GameBackgroundSoundRegulator.h"
#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"

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
	CCAction *moveController = CCMoveTo::create(1.0f, newControllerPosition);
	_popUpView->runAction(moveController);
}

CCNode* RegulateSoundPopUp::makePopUpView()
{

	CCLayerColor *popUpPad = CCLayerColor::create(Color4B::RED, 300, 200);
	popUpPad->ignoreAnchorPointForPosition(false);

	GameSoundEffectsRegulator *soundEffectsRegulator = new GameSoundEffectsRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(soundEffectsRegulator,popUpPad,startGameRegulateSoundEffectsSliderKey);

	GameBackgroundSoundRegulator *backgroundSoundRegulator = new GameBackgroundSoundRegulator();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundSoundRegulator,popUpPad,startGameRegulateSoundSliderKey);

	CCMenuItemImage *closeButtonItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(RegulateSoundPopUp::closePopUp, this));
	closeButtonItem->setScaleX(0.2f);
	closeButtonItem->setScaleY(0.07f);
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButtonItem,popUpPad,startGameRegulateSoundCloseButtonKey);

	return popUpPad;

}

void RegulateSoundPopUp::closePopUp(CCObject* pSender)
{
	CCNode *button = (CCNode*)pSender;
	std::function<void()> buttonCallback = [this](){
		CCAction *moveController = CCMoveTo::create(1.0f, _oldControllerPosition);
		_popUpView->runAction(moveController);
	};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}