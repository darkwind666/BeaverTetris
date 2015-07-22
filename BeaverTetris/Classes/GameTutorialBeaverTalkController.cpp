#include "GameTutorialBeaverTalkController.h"
#include "CocosNodesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameViewElementsKeys.h"
#include "StringsSupporter.h"
#include "GameLocalizationKeys.h"

using namespace cocos2d;

GameTutorialBeaverTalkController::GameTutorialBeaverTalkController(void)
{
	Sprite *beaverTalk = CocosNodesHelper::getSpriteWithKey(gameTutorialBeaverKey);
	this->addChild(beaverTalk);

	CocosNodesHelper::addSpriteToParentNodeWithKey(this, selectLevelBeaverTalkBlobKey);

	LabelTTF *beaverText = GameViewStyleHelper::getStandardLabel();
	beaverText->setFontSize(11.0f);
	beaverText->setDimensions(Size(130, 100));
	beaverText->setString(StringsSupporter::getLocalizedStringFromKey(gameTutorialBeaverTalkLocalizationKey));
	beaverText->setColor(Color3B(89,72,52));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverText, this, selectLevelBeaverTalkTextKey);
}


GameTutorialBeaverTalkController::~GameTutorialBeaverTalkController(void)
{
}


