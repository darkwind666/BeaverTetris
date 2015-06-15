#include "EndGameMenuElementCreator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentLevelDataSource.h"
#include "GameViewStyleHelper.h"
#include "GameStatesHelper.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewElementsDataSource.h"

using namespace cocos2d;
using namespace std;

EndGameMenuElementCreator::EndGameMenuElementCreator(void)
{
}


EndGameMenuElementCreator::~EndGameMenuElementCreator(void)
{
}

Node* EndGameMenuElementCreator::getGameStateLabelWithLocaleString(string aLocaleString)
{
	Sprite *gameStateLabelPad = CocosNodesHelper::getSpriteWithKey(mainGameEndPopResultLabelControllerKey);
	gameStateLabelPad->setName(mainGameEndPopResultLabelControllerKey);
	Label *gameState = GameViewStyleHelper::getStandardLabelWithFontSize(20);
	gameState->setString(StringsSupporter::getLocalizedStringFromKey(aLocaleString));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameState, gameStateLabelPad, mainGameEndPopResultLabelKey);
	return gameStateLabelPad;
}

Node* EndGameMenuElementCreator::getButtonWithCallbackAndKeyAndLocale(ccMenuCallback aCallback, string aKey, string aLocale)
{
	ccMenuCallback callbackFunction = [aCallback](Ref *sender){
		Node *button = (Node*)sender;
		function<void()> callback = [aCallback, sender](){aCallback(sender);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, callback);
	};
	MenuItem *button = GameViewStyleHelper::getCloseButtonWithKeyAndCallbackAndLocalization(aKey, callbackFunction, aLocale);
	Menu *menuForButton = Menu::create();
	menuForButton->setName(aKey);
	menuForButton->addChild(button);
	return menuForButton;
}

Node* EndGameMenuElementCreator::getPlayerAwardLabel()
{
	Sprite *awardPad = CocosNodesHelper::getSpriteWithKey(mainGameEndPopAwardPadKey);
	awardPad->setName(mainGameEndPopAwardPadKey);
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	int playerAward = currentLevelDataSource->getCurrentLevelData().levelAward;
	Label *gameAward = GameViewStyleHelper::getStandardLabelWithFontSize(20);
	gameAward->setString(StringsSupporter::getStringFromNumber(playerAward));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameAward, awardPad, mainGameEndPopAwardLabelKey);
	return awardPad;
}

ccMenuCallback EndGameMenuElementCreator::getFinishGameCallback()
{
	ccMenuCallback nextLevelCallback = [](Ref*){
		CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
		currentPlayerDataSource->cleanPlayer();
		GameStatesHelper::goToScene(kEndGame);
	};
	return nextLevelCallback;
}

ccMenuCallback EndGameMenuElementCreator::getGoToSceneCallback(GameState aState)
{
	ccMenuCallback goToSceneCallback = [aState](Ref*){
		GameStatesHelper::goToScene(aState);
	};
	return goToSceneCallback;
}