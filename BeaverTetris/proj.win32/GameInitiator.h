#pragma once 

class GameViewElementsDataSource;
class GameTransitionsController;

class GameInitiator
{
public:
	GameInitiator();
	~GameInitiator();

	void setInitialState();

private:

	GameViewElementsDataSource *_gameViewElementsDataSource;
	GameTransitionsController *_gameTransitionsController;

};

