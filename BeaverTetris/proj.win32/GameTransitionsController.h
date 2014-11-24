#pragma once

#include "EventHandlerInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include "GameEnums.h"

using namespace std;

class GameTransitionsController : public EventHandlerInterface, public ServiceInterface
{
public:
	GameTransitionsController(void);
	~GameTransitionsController(void);

	void handleEventWithInformation(GameEventInformation aEventInformation);

	void addSceneFactory();
	void addTransitionFromStateToState(GameState stateOne, GameState stateTwo, TransitionType transitionType);

private:

	vector <GameState> _stateFactories;
	vector < vector <TransitionType> > _transitions;

	void goToInitialState(void);
	void changeState(void);
	void goToPreviousState(void);

};