#pragma once 

class GameGraphicsLoader;
class GameTransitionsViewController;

class GameInitiator
{
public:
	GameInitiator();
	~GameInitiator();

	void setInitialState();

private:

	GameGraphicsLoader* getGameGraphicsLoader();
	GameTransitionsViewController* getGameTransitionsViewController();

};

