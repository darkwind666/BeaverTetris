#include "PlayerGameControlsDataSource.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "CurrentDetailController.h"
#include "GameFileExtensionMaker.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

PlayerGameControlsDataSource::PlayerGameControlsDataSource()
{
	_gameViewElementsDataSource = (GameViewElementsDataSource*) ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	_currentDetailController = (CurrentDetailController*) ServiceLocator::getServiceForKey(currentDetailControllerKey);
	_playerControls = getPlayerControls();
}


PlayerGameControlsDataSource::~PlayerGameControlsDataSource(void)
{
}

int PlayerGameControlsDataSource::getPlayerControlsCount()
{
	return _playerControls.size();
}

Vec2 PlayerGameControlsDataSource::getPlayerControlPositionOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return _gameViewElementsDataSource->getElementPositionForKey(controlInformation.imageKey);
}

float PlayerGameControlsDataSource::getPlayerControlRotationForIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return _gameViewElementsDataSource->getElementOffsetForKey(controlInformation.imageKey).x;
}

function<void()> PlayerGameControlsDataSource::getPlayerControlCallbackForIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return controlInformation.callback;
}

string PlayerGameControlsDataSource::getPlayerControlImageForIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	string controlInactiveImage = controlInformation.imageKey + string("Inactive");
	string imageName = GameFileExtensionMaker::getGraphicWithExtension(controlInactiveImage);
	return imageName;
}

int  PlayerGameControlsDataSource::getPlayerControlKeyboardKeyOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return controlInformation.keyboardKey;
}

vector<PlayerControllInformation> PlayerGameControlsDataSource::getPlayerControls()
{
	vector<PlayerControllInformation> playerControls;

	PlayerControllInformation rotateDetail;
	rotateDetail.imageKey = rotateDetailControlKey;
	rotateDetail.keyboardKey = (int)EventKeyboard::KeyCode::KEY_UP_ARROW;
	rotateDetail.callback = [this](){_currentDetailController->rotateDetail();};
	playerControls.push_back(rotateDetail);

	PlayerControllInformation accelerateDetail;
	accelerateDetail.imageKey = accelerateDetailControlKey;
	accelerateDetail.keyboardKey = (int)EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	accelerateDetail.callback = [this](){_currentDetailController->throwDetailOnGameBoard();};
	playerControls.push_back(accelerateDetail);

	PlayerControllInformation moveDetailLeft;
	moveDetailLeft.imageKey = moveDetailLeftControlKey;
	moveDetailLeft.keyboardKey = (int)EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	moveDetailLeft.callback = [this](){_currentDetailController->moveLeftDetail();};
	playerControls.push_back(moveDetailLeft);

	PlayerControllInformation moveDetailRight;
	moveDetailRight.imageKey = moveDetailRightControlKey;
	moveDetailRight.keyboardKey = (int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	moveDetailRight.callback = [this](){_currentDetailController->moveRightDetail();};
	playerControls.push_back(moveDetailRight);

	return playerControls;

}
