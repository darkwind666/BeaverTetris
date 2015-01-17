#include "SelectLevelPlayerStatusController.h"
#include "PlayerStatusDataSource.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

SelectLevelPlayerStatusController::SelectLevelPlayerStatusController(void)
{
	_playerStatusDataSource = new PlayerStatusDataSource();

	_playerName = getStandardLabel();
	_playerScore = getStandardLabel();
	_playerStatusView = getPlayerStatusPad();
	placeAllViewParts();
}


SelectLevelPlayerStatusController::~SelectLevelPlayerStatusController(void)
{
}

LabelTTF* SelectLevelPlayerStatusController::getStandardLabel()
{
	return LabelTTF::create("", "Helvetica", 120);
}

Node* SelectLevelPlayerStatusController::getPlayerStatusPad()
{
	Sprite *padView = CCSprite::create("HelloWorld.png");
	padView->setScale(0.2f);
	padView->setColor(ccColor3B::MAGENTA);
	return padView;
}

void SelectLevelPlayerStatusController::placeAllViewParts()
{
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_playerStatusView, this, selectLevelScenePlayerStatusPadKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_playerName, _playerStatusView, selectLevelScenePlayerStatusNameKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_playerScore, _playerStatusView, selectLevelScenePlayerStatusScoreKey);
}

void SelectLevelPlayerStatusController::onEnterTransitionDidFinish()
{
	_playerName->setString(_playerStatusDataSource->getPlayerName());
	_playerScore->setString(_playerStatusDataSource->getPlayerScore());

	Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(selectLevelScenePlayerStatusPadKey);
	ActionInterval *movePad = MoveTo::create(playerStatusPadActionDuration, finalActionPosition);
	Action *ease = EaseBackOut::create(movePad);
	_playerStatusView->runAction(ease);
}