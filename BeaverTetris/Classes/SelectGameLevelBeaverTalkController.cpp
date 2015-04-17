#include "SelectGameLevelBeaverTalkController.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

SelectGameLevelBeaverTalkController::SelectGameLevelBeaverTalkController(void)
{
	Sprite *beaverTalk = CocosNodesHelper::getSpriteWithKey(selectLevelBeaverTalkKey);
	beaverTalk->setScale(0.7f);
	this->addChild(beaverTalk);
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