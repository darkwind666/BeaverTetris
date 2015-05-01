#include "SelectGameLevelBeaverTalkController.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

SelectGameLevelBeaverTalkController::SelectGameLevelBeaverTalkController(void)
{
	Sprite *beaverTalk = CocosNodesHelper::getSpriteWithKey(selectLevelBeaverTalkKey);
	this->addChild(beaverTalk);

	LabelTTF *beaverText = GameViewStyleHelper::getStandardLabel();
	beaverText->setFontSize(11.0f);
	beaverText->setDimensions(Size(150, 100));
	beaverText->setString(string("Hello, I am glad to see you in game. Help me found my watch please"));
	beaverText->setColor(Color3B(89,72,52));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverText, this, selectLevelBeaverTalkTextKey);
}


SelectGameLevelBeaverTalkController::~SelectGameLevelBeaverTalkController(void)
{
}

void SelectGameLevelBeaverTalkController::showPlayerStatus()
{
	Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(selectLevelBeaverTalkKey);
	ActionInterval *moveBeaver = MoveTo::create(0.3f, finalActionPosition);
	this->runAction(moveBeaver);
}