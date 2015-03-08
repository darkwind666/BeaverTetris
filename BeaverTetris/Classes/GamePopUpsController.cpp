#include "GamePopUpsController.h"
#include "ScreenPopUp.h"

using namespace std;

GamePopUpsController::GamePopUpsController(void)
{
   _messageListnersPopUps = map<PopUpType, ScreenPopUp*>();
}


GamePopUpsController::~GamePopUpsController(void)
{

}


void GamePopUpsController::showPopUp(PopUpType aPopUp)
{
	ScreenPopUp *popUp = _messageListnersPopUps[aPopUp];
	popUp->showPopUp();
}

void GamePopUpsController::subscribePopUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	_messageListnersPopUps[aMessage] = aPopUp;
}

void GamePopUpsController::unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	map<PopUpType, ScreenPopUp*>::iterator unSubscribePopUp;
	unSubscribePopUp = _messageListnersPopUps.find(aMessage);
	_messageListnersPopUps.erase(unSubscribePopUp);
}
