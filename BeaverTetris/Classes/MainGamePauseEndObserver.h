#pragma once
class MainGamePauseEndObserver
{
public:
	MainGamePauseEndObserver(void);
	virtual ~MainGamePauseEndObserver(void);

	virtual void pauseWasEnded() = 0;

};

