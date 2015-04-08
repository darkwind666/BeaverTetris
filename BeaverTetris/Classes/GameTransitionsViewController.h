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
	ScenesFactory *_scenesFactory;

	cocos2d::Scene* getSceneWithTransitionForId(GameState aSceneId);
	cocos2d::Scene* getSceneWithStandartTransition(cocos2d::Scene* aScene);

};