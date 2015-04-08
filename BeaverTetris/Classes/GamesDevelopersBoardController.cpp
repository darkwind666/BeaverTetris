#include "GamesDevelopersBoardController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "StringsSupporter.h"
#include "DevelopersNamesConstants.h"

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
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperProgrammerKey, programmerKey, programmerNameKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperDesignerKey, designerKey, designerNameKey);
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
	Sprite *developerPad = Sprite::create("HelloWorld.png");
	developerPad->setScaleX(0.4f);
	developerPad->setScaleY(0.15f);
	developerPad->setColor(Color3B::BLACK);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developerPad, this, aPadKey);
	return developerPad;
}

Node* GamesDevelopersBoardController::getDeveloperLabelWithString(string aString)
{
	LabelTTF *playerNameLabel = GameViewStyleHelper::getStandardLabel();
	playerNameLabel->setFontSize(50);
	playerNameLabel->setString(aString);
	return playerNameLabel;
}
