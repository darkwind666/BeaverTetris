#pragma once

#include "proj.win32\EventHandlerInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include <map>
#include "proj.win32\GameEnums.h"
#include "GameStructures.h"

class ScenesTransitionsFactory;
class ScenesFactory;

class GameTransitionsViewController : public  ServiceInterface
{
public:
	GameTransitionsViewController(ScenesTransitionsFactory *aScenesTransitionsFactory, ScenesFactory *aScenesFactory);
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