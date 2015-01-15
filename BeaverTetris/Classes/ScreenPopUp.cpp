#include "ScreenPopUp.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GamePopUpsController.h"

ScreenPopUp::ScreenPopUp(void)
{
}


ScreenPopUp::~ScreenPopUp(void)
{
}

void ScreenPopUp::showPopUp()
{

}

void ScreenPopUp::subscribePopUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gamePopUpsControllerKey);
	popUpsController->subscribePopUpToMessage(aPopUp, aMessage);
}

void ScreenPopUp::unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gamePopUpsControllerKey);
	popUpsController->unSubscribePupUpToMessage(aPopUp, aMessage);
}
