#include "GameWorldBackgroundController.h"
#include "MainGameBackgroundDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "StringsSupporter.h"

using namespace cocos2d;

GameWorldBackgroundController::GameWorldBackgroundController(void)
{
	_mainGameBackgroundDataSource = new MainGameBackgroundDataSource();
	makeControllerView();
}


GameWorldBackgroundController::~GameWorldBackgroundController(void)
{
}

void GameWorldBackgroundController::makeControllerView()
{
	Sprite *backgroundImage = CocosNodesHelper::getSpriteWithKey(mainGameBackgroundControllerKey);
	Sprite *backgroundPadImage = CocosNodesHelper::getSpriteWithKey(mainGameBackgroundPadKey);
	this->addChild(backgroundImage);
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, mainGameBackgroundPadKey);
}

void GameWorldBackgroundController::onEnterTransitionDidFinish()
{
	string soundName = getMainGameBackgroundMusicName();
	string mainGameBackgroundMusicWithExtension = GameFileExtensionMaker::getSoundWithExtension(soundName);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(mainGameBackgroundMusicWithExtension);
}

string GameWorldBackgroundController::getMainGameBackgroundMusicName()
{
	srand(time(0));
	int flag = GameHelper::getRandomNumberFromUpInterval(3) + 1;
	string soundIndex = StringsSupporter::getStringFromNumber(flag);
	string soundName = backgroundSoundKey + soundIndex;
	return soundName;
}

void GameWorldBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}