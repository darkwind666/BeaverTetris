#pragma once

#include "EventHandlerInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include <map>
#include "GameEnums.h"
#include "GameStructures.h"

class GameTransitionsViewController 
{
public:
	GameTransitionsViewController(void);
	~GameTransitionsViewController(void);

	void addSceneFactory();
	void addTransitionFromStateToState(GameState stateOne, GameState stateTwo, TransitionType transitionType);

	void goToInitialState(void);
	void changeState(void);
	void goToPreviousState(void);


private:

	std::vector <GameState> _stateFactories;
	std::vector < std::vector <TransitionType> > _transitions;

};