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

void ScreenPopUp::closePopUp()
{

}

void subscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gamePopUpsControllerKey);
	popUpsController->subscribePupUpToMessage(aPopUp, aMessage);
}

void unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gamePopUpsControllerKey);
	popUpsController->unSubscribePupUpToMessage(aPopUp, aMessage);
}