#pragma once

class GameTimeStepController;

class CurrentDetailAccelerationDelegate
{
public:
	CurrentDetailAccelerationDelegate(void);
	~CurrentDetailAccelerationDelegate(void);

	void accelerateCurrentDetail();
	void stopAcceleratingCurrentDetail();
	void update();

private:

	GameTimeStepController *_gameTimeStepController;
	bool _currentDetailAccelerationActive;

	bool availableAccelerateEvent();
	int getUpdateIntervalAfterAcceleration();

};

