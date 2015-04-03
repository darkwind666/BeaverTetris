#include "GameWorldBackgroundController.h"
#include "MainGameBackgroundDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"

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
	LayerColor *backgroundView = LayerColor::create(Color4B::ORANGE);
	backgroundView->ignoreAnchorPointForPosition(false);
	this->addChild(backgroundView);
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
	string soundName  = string();
	srand(time(0));
	int flag = GameHelper::getRandomNumberFromUpInterval(2);
	if (flag == 0)
	{
		soundName = backgroundSound1Key;
	}
	else
	{
		soundName = backgroundSound2Key;
	}
	return soundName;
}

void GameWorldBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}