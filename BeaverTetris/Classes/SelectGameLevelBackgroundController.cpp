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
	CocosNodesHelper::addSpriteToParentNodeWithKey(background, selectLevelBackgroundRightKey);
	CocosNodesHelper::addSpriteToParentNodeWithKey(background, selectLevelBackgroundLeftKey);
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
