#include "TimeAccelerationEvent.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"

TimeAccelerationEvent::TimeAccelerationEvent(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_currentUpdateState = 0;
	_currentEventState = 0;
}


TimeAccelerationEvent::~TimeAccelerationEvent(void)
{
}

bool TimeAccelerationEvent::eventTime(void)
{
	bool eventTime = false;

	if (_currentUpdateState >= timeAccelerationEventTimeIntervalConstant)
	{
		eventTime = true;
	}
	return eventTime;
}

void TimeAccelerationEvent::runEvent(void)
{
	_currentEventState = timeAccelerationEventActiveTimeConstant;
	_gameTimeStepController->setUpdateInterval(acceleratedUpdateInterval);
	_currentUpdateState = 0;
}

void TimeAccelerationEvent::updateEvent(void)
{
	_currentUpdateState++;

	if (_currentEventState <= 0)
	{
		_gameTimeStepController->setUpdateInterval(normalUpdateInterval);
	}
	else
	{
		_currentEventState--;
	}

}