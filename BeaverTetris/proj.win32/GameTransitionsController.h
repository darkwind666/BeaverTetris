#pragma once

#include "GameEnums.h"
#include <vector>

using namespace std;

class GameTransitionsController
{
public:
	GameTransitionsController(void);
	~GameTransitionsController(void);

	void goToInitialState(void);
	void goToState(GameState aGameState);
	void goToPreviousState(void);

	void addSceneFactory();
	void addTransitionFromStateToState(GameState stateOne, GameState stateTwo, TransitionType transitionType);

private:

	vector <GameState> _stateFactories;
	vector < vector <TransitionType> > _transitions;

};