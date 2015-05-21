#pragma once

#include "cocos2d.h"

class GameWorldController;
class CurrentPlayerDataSource;
class GameTutorialsFactory;

class GameTutorialController : public cocos2d::Node
{
public:
	GameTutorialController(GameWorldController *aGameWorld);
	~GameTutorialController(void);

	virtual void onEnterTransitionDidFinish();
	void endTutorial();

private:

	GameWorldController *_gameWorldController;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameTutorialsFactory *_gameTutorialsFactory;
	std::string _currentLevelName;

	std::string getCurrentLevelName();
	void startTutorial();

};

