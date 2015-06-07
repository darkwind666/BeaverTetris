#pragma once 

#include "cocos2d.h"
#include <vector>
#include <functional>

class DetailForTutorialController;
class PlayerActionsForTutorialController;
class PlayerScoreForTutorialController;
class TetraminosForTutorialController;
class ExplosionsForTutorialController;
class VictoryConditionForTutorialController;

class GameTutorialsAnimationController : public cocos2d::Node
{
public:
	GameTutorialsAnimationController(void);
	~GameTutorialsAnimationController(void);

	void cleanCurrentTutorial();

	cocos2d::FiniteTimeAction* getPlayerControllsTutorial();
	cocos2d::FiniteTimeAction* getPlayerReduceLineTutorial();
	cocos2d::FiniteTimeAction* getPlayerReduceHorizontalCombinationTutorial();
	cocos2d::FiniteTimeAction* getPlayerReduceVerticalCombinationTutorial();
	cocos2d::FiniteTimeAction* getPlayerUseRocketSpellTutorial();
	cocos2d::FiniteTimeAction* getPlayerFightWithBossTutorial();
	cocos2d::FiniteTimeAction* getPlayerUseRandomExplosionsSpellTutorial();
	cocos2d::FiniteTimeAction* getPlayerUseFirestormSpellTutorial();
	cocos2d::FiniteTimeAction* getPlayerUseCohesionSpellTutorial();

private:

	DetailForTutorialController *_detailController;
	PlayerActionsForTutorialController *_playerActionsController;
	PlayerScoreForTutorialController *_scoreController;
	TetraminosForTutorialController *_tetraminosController;
	ExplosionsForTutorialController *_explosionsController;
	VictoryConditionForTutorialController *_victoryConditionController;

};

