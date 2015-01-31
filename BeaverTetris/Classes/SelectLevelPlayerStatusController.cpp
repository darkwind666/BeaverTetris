#include "SelectLevelPlayerStatusController.h"
#include "PlayerStatusDataSource.h"
#include "GameElementsDataHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

SelectLevelPlayerStatusController::SelectLevelPlayerStatusController(void)
{
	_playerStatusDataSource = new PlayerStatusDataSource();
	_delegate = NULL;
	_playerName = GameViewStyleHelper::getStandardLabel();
	_playerScore = GameViewStyleHelper::getStandardLabel();
	_playerStatusView = getPlayerStatusPad();
	placeAllViewParts();
}


SelectLevelPlayerStatusController::~SelectLevelPlayerStatusController(void)
{
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

Action* SelectLevelPlayerStatusController::getShowControllerAnimation()
{
	Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(selectLevelScenePlayerStatusPadKey);
	ActionInterval *movePad = MoveTo::create(playerStatusPadActionDuration, finalActionPosition);
	FiniteTimeAction *ease = EaseBackOut::create(movePad);
	FiniteTimeAction *callback = getCallback();
	Action *sequence = Sequence::create(ease, callback, NULL);
	return sequence;
}

FiniteTimeAction* SelectLevelPlayerStatusController::getCallback()
{
	FiniteTimeAction *callback = CallFunc::create([this](){
		if (_delegate)
		{
			_delegate->showPlayerStatus();
		}
	});
	return callback;
}

void SelectLevelPlayerStatusController::showPlayerStatus()
{
	_playerName->setString(_playerStatusDataSource->getPlayerName());
	_playerScore->setString(_playerStatusDataSource->getPlayerScore());
	
	Action *showControllerAction = getShowControllerAnimation();
	_playerStatusView->runAction(showControllerAction);
}

void SelectLevelPlayerStatusController::setDelegate(PlayerStatusDelegateInterface *aDelegate)
{
	_delegate = aDelegate;
}