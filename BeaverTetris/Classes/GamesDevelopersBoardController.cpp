#include "GamesDevelopersBoardController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "StringsSupporter.h"
#include "GameLocalizationKeys.h"

using namespace cocos2d;
using namespace std;

GamesDevelopersBoardController::GamesDevelopersBoardController(void)
{
	makeBoardView();
}

GamesDevelopersBoardController::~GamesDevelopersBoardController(void)
{
}

void GamesDevelopersBoardController::makeBoardView()
{
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, gameDevelopersBoardPadKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperProgrammerKey, gameDeveloperProgrammerLocalizationKey, gameDeveloperProgrammerNameLocalizationKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperDesignerKey, gameDeveloperDesignerLocalizationKey, gameDeveloperDesignerNameLocalizationKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperMusicianKey, gameDeveloperMusicianLocalizationKey, gameDeveloperMusicianNameLocalizationKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperGameEngineKey, gameDeveloperGameEngineLocalizationKey, gameDeveloperGameEngineNameLocalizationKey);
	GameViewStyleHelper::addBackButtonToParentNodeWithKey(this, gameDevelopersGoToMainMenuButtonKey);
}

void GamesDevelopersBoardController::makeViewWithPadAndFunctionAndNameKeys(string aPadKey, string aFunctionKey, string aNameKey)
{
	Node *developerPad = getDeveloperPadWithKey(aPadKey);
	Node *developerFunctionLabel = getDeveloperLabelWithString(aFunctionKey);
	Node *developerNameLabel = getDeveloperLabelWithString(aNameKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developerFunctionLabel, developerPad, gameDevelopersFunctionLabelKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developerNameLabel, developerPad, gameDevelopersNameLabelKey);
}

Node* GamesDevelopersBoardController::getDeveloperPadWithKey(string aPadKey)
{
	Sprite *developerPad = CocosNodesHelper::getSpriteWithKey(gameDevelopersBoardPlacePadKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developerPad, this, aPadKey);
	return developerPad;
}

Node* GamesDevelopersBoardController::getDeveloperLabelWithString(string aString)
{
	LabelTTF *playerNameLabel = GameViewStyleHelper::getStandardLabel();
	playerNameLabel->setFontSize(12);
	playerNameLabel->setString(StringsSupporter::getLocalizedStringFromKey(aString));
	return playerNameLabel;
}