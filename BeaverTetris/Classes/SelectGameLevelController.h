#pragma once

#include "cocos2d.h"
#include <vector>

class GameLevelsMenuDataSource;

class SelectGameLevelController : public cocos2d::CCNode
{
public:
	SelectGameLevelController(void);
	~SelectGameLevelController(void);

	virtual void onEnterTransitionDidFinish();

private:

	GameLevelsMenuDataSource *_gameLevelsMenuDataSource;
	cocos2d::CCMenu* _menuView;

	void makeScrollableMenuWithBackground(cocos2d::CCMenu* aMenu);
	cocos2d::CCNode* makeScrollableMenuWithContent(cocos2d::CCNode* aContentContainer);

	std::vector<cocos2d::CCMenuItemImage*> makeLevelsIcons();
	void addLevelIconsToMenu(std::vector<cocos2d::CCMenuItemImage*>  aLevelIcons);
	cocos2d::CCAction* makeMenuAnimationWithIcons(std::vector<cocos2d::CCMenuItemImage*>  aLevelIcons);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> makeActionWithEachIcon(std::vector<cocos2d::CCMenuItemImage*>  aLevelIcons);

	void buttonWasPressed(cocos2d::CCObject* pSender);

};

