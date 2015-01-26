#include "PlayerGameControlsDataSource.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"

using namespace std;
using namespace cocos2d;

PlayerGameControlsDataSource::PlayerGameControlsDataSource()
{
	_gameViewElementsDataSource = (GameViewElementsDataSource*) ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	_playerControls = getPlayerControls();
}


PlayerGameControlsDataSource::~PlayerGameControlsDataSource(void)
{
}

int PlayerGameControlsDataSource::getPlayerControlsCount()
{
	return _playerControls.size();
}

string PlayerGameControlsDataSource::getPlayerControlIconImageOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return _gameViewElementsDataSource->getElementImageForKey(controlInformation.imageKey);
}

Vec2 PlayerGameControlsDataSource::getPlayerControlPositionOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return _gameViewElementsDataSource->getElementPositionForKey(controlInformation.imageKey);
}

function<void()> PlayerGameControlsDataSource::getPlayerControlCallbackForIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return controlInformation.callback;
}

vector<PlayerControllInformation> PlayerGameControlsDataSource::getPlayerControls()
{
	vector<PlayerControllInformation> playerControls;

	PlayerControllInformation rotateDetail;
	rotateDetail.imageKey = rotateDetailControlKey;
	rotateDetail.callback = [](){};
	playerControls.push_back(rotateDetail);

	PlayerControllInformation accelerateDetail;
	accelerateDetail.imageKey = accelerateDetailControlKey;
	accelerateDetail.callback = [](){};
	playerControls.push_back(accelerateDetail);

	PlayerControllInformation moveDetailLeft;
	moveDetailLeft.imageKey = moveDetailLeftControlKey;
	moveDetailLeft.callback = [](){};
	playerControls.push_back(moveDetailLeft);

	PlayerControllInformation moveDetailRight;
	moveDetailRight.imageKey = moveDetailRightControlKey;
	moveDetailRight.callback = [](){};
	playerControls.push_back(moveDetailRight);

	PlayerControllInformation pauseGame;
	pauseGame.imageKey = pauseGameControlKey;
	pauseGame.callback = [](){};
	playerControls.push_back(pauseGame);

	return playerControls;

}
