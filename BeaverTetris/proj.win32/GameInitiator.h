#pragma once 

class GameViewElementsDataSource;
class EventDispatcher;

class GameInitiator
{
public:
	GameInitiator();
	~GameInitiator();

	void setInitialState();

private:

	GameViewElementsDataSource *_gameViewElementsDataSource;
	EventDispatcher *_eventDispatcher;

};

