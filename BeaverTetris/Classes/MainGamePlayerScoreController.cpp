#include "MainGamePlayerScoreController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "StringsSupporter.h"

using namespace cocos2d;
using namespace std;

MainGamePlayerScoreController::MainGamePlayerScoreController(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_scoreView = GameViewStyleHelper::getStandardLabel();
	_scoreView->setColor(Color3B(20, 61, 62));
	makeControllerView();
}

MainGamePlayerScoreController::~MainGamePlayerScoreController(void)
{
}

void MainGamePlayerScoreController::makeControllerView()
{
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, playerScoreControllerBackgroundKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_scoreView, this, playerScoreControllerCountKey);
}

void MainGamePlayerScoreController::update(float delta)
{
	int playerScoreCount = _currentPlayerDataSource->getPlayerScore();
	string playerScore = StringsSupporter::getStringFromNumber(playerScoreCount);
	_scoreView->setString(playerScore);
}