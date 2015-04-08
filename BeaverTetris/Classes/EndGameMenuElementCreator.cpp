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

Node* EndGameMenuElementCreator::getButtonWithCallbackAndColor(function<void()> aCallback, cocos2d::Color3B aColor)
{
	MenuItemImage *button = MenuItemImage::create("HelloWorld.png","HelloWorld.png");
	button->setScaleX(0.2f);
	button->setScaleY(0.07f);
	button->setColor(aColor);
	button->setCallback([aCallback](Ref *sender){
		Node *button = (Node*)sender;
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, aCallback);
	});
	Menu *menuForButton = Menu::create();
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

function<void()> EndGameMenuElementCreator::getFinishGameCallback()
{
	function<void()> nextLevelCallback = [](){
		CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
		currentPlayerDataSource->cleanPlayer();
		GameStatesHelper::goToScene(kRecords);
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