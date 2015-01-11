#pragma once

#include "ServiceInterface.h"
#include <vector>
#include <map>
#include "GameEnums.h"
#include "GameStructures.h"

class ScenesTransitionsFactory;
class ScenesFactory;

class GameTransitionsViewController : public  ServiceInterface
{
public:
	GameTransitionsViewController();
	~GameTransitionsViewController(void);

	void addSceneFactory();

	void goToInitialState(void);
	void changeOnNewState(GameState aNewGameState);

private:

	std::vector <GameState> _stateFactories;
	std::vector < std::vector <TransitionType> > _transitions;
	ScenesFactory *_scenesFactory;

	cocos2d::CCScene* getSceneWithTransitionForId(GameState aSceneId);
	cocos2d::CCScene* getSceneWithStandartTransition(cocos2d::CCScene* aScene);

};