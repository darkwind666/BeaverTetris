#include "SelectGameLevelBackgroundController.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

SelectGameLevelBackgroundController::SelectGameLevelBackgroundController(void)
{
	Sprite *background = CocosNodesHelper::getSpriteWithKey(selectLevelBackgroundKey);

	Sprite *backgroundLeftEarth = CocosNodesHelper::getSpriteWithKey(selectLevelBackgroundLeftKey);
	backgroundLeftEarth->setScale(0.95f);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundLeftEarth, background, selectLevelBackgroundLeftKey);

	CocosNodesHelper::addSpriteToParentNodeWithKey(background, selectLevelBackgroundRightKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background, this, selectLevelBackgroundKey);
}


SelectGameLevelBackgroundController::~SelectGameLevelBackgroundController(void)
{
}

void SelectGameLevelBackgroundController::onEnterTransitionDidFinish()
{
	string birdSoundEffect = GameFileExtensionMaker::getSoundWithExtension(birdInForestSoundKey);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(birdSoundEffect);
}

void SelectGameLevelBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}
