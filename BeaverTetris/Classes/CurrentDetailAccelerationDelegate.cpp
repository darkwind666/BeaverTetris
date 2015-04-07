#include "CurrentDetailAccelerationDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "TimeAccelerationEvent.h"
#include "GameDesignConstants.h"
#include "GameTimeStepController.h"

CurrentDetailAccelerationDelegate::CurrentDetailAccelerationDelegate(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_currentDetailAccelerationActive = false;
}


CurrentDetailAccelerationDelegate::~CurrentDetailAccelerationDelegate(void)
{
}

void CurrentDetailAccelerationDelegate::accelerateCurrentDetail()
{
	_gameTimeStepController->setUpdateInterval(acceleratedCurrentDetailUpdateInterval);
	_currentDetailAccelerationActive = true;
}

void CurrentDetailAccelerationDelegate::stopAcceleratingCurrentDetail()
{
	if (_currentDetailAccelerationActive)
	{
		int updateIntervalAfterAcceleration = getUpdateIntervalAfterAcceleration();
		_gameTimeStepController->setUpdateInterval(updateIntervalAfterAcceleration);
		_currentDetailAccelerationActive = false;
	}
}

int CurrentDetailAccelerationDelegate::getUpdateIntervalAfterAcceleration()
{
	int updateIntervalAfterAcceleration = normalUpdateInterval;
	if (availableAccelerateEvent())
	{
		TimeAccelerationEvent *timeAccelerationEvent = (TimeAccelerationEvent*)ServiceLocator::getServiceForKey(timeAccelerationEventModelKey);
		if (timeAccelerationEvent->eventActive())
		{
			updateIntervalAfterAcceleration = timeAccelerationEvent->getAcceleratedUpdateInterval();
		}
	}
	return updateIntervalAfterAcceleration;
}

void CurrentDetailAccelerationDelegate::update()
{
	if (_currentDetailAccelerationActive)
	{
		_gameTimeStepController->setUpdateInterval(acceleratedCurrentDetailUpdateInterval);
	}
}

bool CurrentDetailAccelerationDelegate::availableAccelerateEvent()
{
	bool availableAccelerateEvent = false;
	ServiceInterface *service = ServiceLocator::getServiceForKey(timeAccelerationEventModelKey);
	if (service)
	{
		availableAccelerateEvent = true;
	}
	return availableAccelerateEvent;
}

