#include "TimeAccelerationEvent.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameTimeStepController.h"

TimeAccelerationEvent::TimeAccelerationEvent(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_currentUpdateState = 0;
	_currentEventState = 0;
	_eventActive = false;
}


TimeAccelerationEvent::~TimeAccelerationEvent(void)
{
}

void TimeAccelerationEvent::updateEvent(void)
{
	if (_eventActive)
	{
		stepEventActive();
	}
	else
	{
		stepTimeInterval();
	}
}

void TimeAccelerationEvent::stepEventActive()
{
	_currentEventState++;
	if (_currentEventState >= timeAccelerationEventActiveTimeConstant)
	{
		_currentEventState = 0;
		_eventActive = false;
		_gameTimeStepController->setUpdateInterval(normalUpdateInterval);
	}
}

void TimeAccelerationEvent::stepTimeInterval()
{
	_currentUpdateState++;
	if (_currentUpdateState >= timeAccelerationEventTimeIntervalConstant)
	{
		_currentEventState = 0;
		_eventActive = true;
		_gameTimeStepController->setUpdateInterval(acceleratedUpdateInterval);
		_currentUpdateState = 0;
	}
}