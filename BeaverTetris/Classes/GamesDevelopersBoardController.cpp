#include "GamesDevelopersBoardController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "StringsSupporter.h"
#include "DevelopersNamesConstants.h"
#include "GameKeyWithSuffixSupporter.h"
#include "GameStatesHelper.h"
#include "GameEnums.h"
#include "MouseOverMenuItem.h"

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
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperProgrammerKey, programmerKey, programmerNameKey);
	makeViewWithPadAndFunctionAndNameKeys(gameDeveloperDesignerKey, designerKey, designerNameKey);
	createBackToMainMenuButton();
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
	playerNameLabel->setString(aString);
	return playerNameLabel;
}

void GamesDevelopersBoardController::createBackToMainMenuButton()
{
	MenuItem *goToMainMenuButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(goToMainMenuButton,this,gameDevelopersGoToMainMenuButtonKey);
}

MenuItem* GamesDevelopersBoardController::getCloseButton()
{
	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};
	
	string inactiveImageName = GameKeyWithSuffixSupporter::makeUnselectedImageForKey(gameDevelopersGoToMainMenuButtonKey);
	string activeImageName = GameKeyWithSuffixSupporter::makeSelectedImageForKey(gameDevelopersGoToMainMenuButtonKey);
	MouseOverMenuItem *closeButtonItem = new MouseOverMenuItem(activeImageName,inactiveImageName,callback);
	return closeButtonItem;
}