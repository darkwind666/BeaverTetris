#include "PlayerGameControlsDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameEventsFactory.h"

using namespace std;
using namespace cocos2d;

PlayerGameControlsDataSource::PlayerGameControlsDataSource(GameViewElementsDataSource *aGameViewElementsDataSource)
{
	_gameViewElementsDataSource = aGameViewElementsDataSource;
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
	return _gameViewElementsDataSource->getElementImageForKey(controlInformation.controlKey);
}

Vec2 PlayerGameControlsDataSource::getPlayerControlPositionOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return _gameViewElementsDataSource->getElementPositionForKey(controlInformation.controlKey);
}

GameEvent PlayerGameControlsDataSource::getPlayerControlEventOnIndex(int aIndex)
{
	PlayerControllInformation controlInformation = _playerControls[aIndex];
	return controlInformation.controlEvent;
}

vector<PlayerControllInformation> PlayerGameControlsDataSource::getPlayerControls()
{
	vector<PlayerControllInformation> playerControls = vector<PlayerControllInformation>();

	PlayerControllInformation controlInformation1;
	controlInformation1.controlKey = playerControl1Key;
	controlInformation1.controlEvent = GameEventsFactory::makePlayerActionInGameEventWithKey(kTurnDetailLeft);

	PlayerControllInformation controlInformation2;
	controlInformation2.controlKey = playerControl1Key;
	controlInformation2.controlEvent = GameEventsFactory::makePlayerActionInGameEventWithKey(kTurnDetailRight);

	PlayerControllInformation controlInformation3;
	controlInformation3.controlKey = playerControl1Key;
	controlInformation3.controlEvent = GameEventsFactory::makePlayerActionInGameEventWithKey(kAccelerateDetail);

	PlayerControllInformation controlInformation4;
	controlInformation4.controlKey = playerControl1Key;
	controlInformation4.controlEvent = GameEventsFactory::makePlayerActionInGameEventWithKey(kRotateDetail);

	PlayerControllInformation controlInformation5;
	controlInformation5.controlKey = playerControl1Key;
	controlInformation5.controlEvent = GameEventsFactory::makeGoToPopUpEventWithKey(kPauseGamePopUp);

	playerControls.push_back(controlInformation1);
	playerControls.push_back(controlInformation2);
	playerControls.push_back(controlInformation3);
	playerControls.push_back(controlInformation4);
	playerControls.push_back(controlInformation5);

	return playerControls;

}
