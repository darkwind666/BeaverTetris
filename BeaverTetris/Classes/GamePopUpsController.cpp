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

void GamePopUpsController::subscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	_messageListnersPopUps[aMessage] = aPopUp;
}

void GamePopUpsController::unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	map<PopUpType, ScreenPopUp*>::iterator unSubscribePopUp ;
	unSubscribePopUp = find(_messageListnersPopUps.begin(), _messageListnersPopUps.end(), aMessage);
	_messageListnersPopUps.erase(unSubscribePopUp);
}
