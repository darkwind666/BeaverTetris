#pragma once
class GameEventsDataSource
{
public:
	GameEventsDataSource(void);
	~GameEventsDataSource(void);

	bool availableEvent(void);
	void runAvailableEvent(void);

};

