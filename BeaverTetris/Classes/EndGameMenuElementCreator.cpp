#include "EndGameMenuElementCreator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentLevelDataSource.h"
#include "GameViewStyleHelper.h"
#include "GameStatesHelper.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"

using namespace cocos2d;
using namespace std;

EndGameMenuElementCreator::EndGameMenuElementCreator(void)
{
}


EndGameMenuElementCreator::~EndGameMenuElementCreator(void)
{
}

Node* EndGameMenuElementCreator::getGameStateLabelWithString(string stateLabelString)
{
	LabelTTF *gameState = GameViewStyleHelper::getStandardLabel();
	gameState->setFontSize(20);
	gameState->setString(stateLabelString);
	return gameState;
}

Node* EndGameMenuElementCreator::getButtonWithCallbackAndColor(function<void()> aCallback, cocos2d::ccColor3B aColor)
{
	CCMenuItemImage *button = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png");
	button->setScaleX(0.2f);
	button->setScaleY(0.07f);
	button->setColor(aColor);
	button->setCallback([aCallback](Ref *sender){
		Node *button = (Node*)sender;
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, aCallback);
	});
	CCMenu *menuForButton = CCMenu::create();
	menuForButton->addChild(button);
	return menuForButton;
}

Node* EndGameMenuElementCreator::getPlayerAwardLabel()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	int playerAward = currentLevelDataSource->getCurrentLevelData().levelAward;
	Node *playerAwardLabel = getGameStateLabelWithString(StringsSupporter::getStringFromNumber(playerAward));
	return playerAwardLabel;
}

function<void()> EndGameMenuElementCreator::getNextLevelCallback()
{
	function<void()> nextLevelCallback = [](){
		CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
		int currentLevelIndex = currentPlayerDataSource->getSelectedGameLevelIndex();
		currentPlayerDataSource->setSelectedGameLevelIndex(currentLevelIndex + 1);
		GameStatesHelper::goToScene(kPlayGame);
	};
	return nextLevelCallback;
}

function<void()> EndGameMenuElementCreator::getGoToSceneCallback(GameState aState)
{
	function<void()> goToSceneCallback = [aState](){
		GameStatesHelper::goToScene(aState);
	};
	return goToSceneCallback;
}