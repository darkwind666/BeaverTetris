#include "SelectGameLevelBeaverOnRaftController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;

SelectGameLevelBeaverOnRaftController::SelectGameLevelBeaverOnRaftController(void)
{
	Sprite *beaverOnRaft = CocosNodesHelper::getSpriteWithKey(selectLevelBeaverOnRaftKey);
	Vec2 beaverOnRaftPosition = getPositionForBeaverOnRaft();
	beaverOnRaft->setPosition(beaverOnRaftPosition);
	this->addChild(beaverOnRaft);
}


SelectGameLevelBeaverOnRaftController::~SelectGameLevelBeaverOnRaftController(void)
{
}

Vec2 SelectGameLevelBeaverOnRaftController::getPositionForBeaverOnRaft()
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	int completedLevelsCount = currentPlayerDataSource->getPlayerCompletedLevelsCount();
	GameLevelsDataSource *gameLevelsDataSource = (GameLevelsDataSource*)ServiceLocator::getServiceForKey(gameLevelsDataSourceKey);
	string maxWinGameLevelKey = gameLevelsDataSource->getLevelNameForIndex(completedLevelsCount);
	Vec2 beaverOnRaftPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(maxWinGameLevelKey);
	return beaverOnRaftPosition;
}
