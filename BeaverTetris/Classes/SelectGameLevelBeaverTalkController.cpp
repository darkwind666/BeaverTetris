#include "SelectGameLevelBeaverTalkController.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"
#include "StringsSupporter.h"
#include "GameLocalizationKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"

using namespace cocos2d;

SelectGameLevelBeaverTalkController::SelectGameLevelBeaverTalkController(void)
{
	Sprite *beaverTalk = CocosNodesHelper::getSpriteWithKey(selectLevelBeaverTalkKey);
	this->addChild(beaverTalk);

	CocosNodesHelper::addSpriteToParentNodeWithKey(this, selectLevelBeaverBlobTalkKey);

	LabelTTF *beaverText = GameViewStyleHelper::getStandardLabel();
	beaverText->setFontSize(21.0f);
	beaverText->setDimensions(Size(230, 200));
	string beaverSpeech = getBeaverSpeech();
	beaverText->setString(StringsSupporter::getLocalizedStringFromKey(beaverSpeech));
	beaverText->setColor(Color3B(89,72,52));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverText, this, selectLevelBeaverTalkTextKey);
}


SelectGameLevelBeaverTalkController::~SelectGameLevelBeaverTalkController(void)
{
}

string SelectGameLevelBeaverTalkController::getBeaverSpeech()
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	GameLevelsDataSource *gameLevelsDataSource = (GameLevelsDataSource*)ServiceLocator::getServiceForKey(gameLevelsDataSourceKey);
	int completedLevelsCount = currentPlayerDataSource->getPlayerCompletedLevelsCount();
	string beaverSpeech = gameLevelsDataSource->getLevelNameForIndex(completedLevelsCount);
	return beaverSpeech;
}

void SelectGameLevelBeaverTalkController::showPlayerStatus()
{
	Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(selectLevelBeaverTalkKey);
	ActionInterval *moveBeaver = MoveTo::create(0.6f, finalActionPosition);
	this->runAction(moveBeaver);
}