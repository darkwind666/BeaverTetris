#include "GameTutorialShowLevelIcon.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"

using namespace cocos2d;

GameTutorialShowLevelIcon::GameTutorialShowLevelIcon(void)
{
	_showMark = false;

	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	if (currentPlayerDataSource->isThereCurentPlayer())
	{
		if (currentPlayerDataSource->getPlayerCompletedLevelsCount() == 0)
		{
			_showMark = true;
		}
	}

}


GameTutorialShowLevelIcon::~GameTutorialShowLevelIcon(void)
{
}

void GameTutorialShowLevelIcon::showIcon()
{
	if (_showMark)
	{
		_currentLevelMark = CocosNodesHelper::getSpriteWithKey(gameTutorialShowLevelIconKey);
		_currentLevelMark->setRotation(90.0f);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(_currentLevelMark, this, gameTutorialShowLevelIconKey);
		Vec2 finalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialShowLevelIconKey);
		FiniteTimeAction *moveDown = MoveTo::create(0.5f, finalPosition);
		FiniteTimeAction *moveUp = MoveTo::create(0.5f, _currentLevelMark->getPosition());
		ActionInterval *sequence = Sequence::create(moveDown, moveUp, nullptr);
		FiniteTimeAction *repeat = RepeatForever::create(sequence);
		_currentLevelMark->runAction(repeat);
	}
}

void GameTutorialShowLevelIcon::onExitTransitionDidStart()
{
	if (_showMark)
	{
		_currentLevelMark->stopAllActions();
	}
}
