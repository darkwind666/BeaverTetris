#pragma once

#include "cocos2d.h"
#include <vector>

class GameLevelsMenuDataSource;

class SelectGameLevelController : public cocos2d::CCNode
{
public:
	SelectGameLevelController(void);
	~SelectGameLevelController(void);

private:

	GameLevelsMenuDataSource *_gameLevelsMenuDataSource;
	cocos2d::CCNode* _menuView;

	std::vector<cocos2d::CCMenuItemImage*> makeLevelsIcons();
	cocos2d::CCNode* makeScrollableMenuViewWithLevelIcons(std::vector<cocos2d::CCMenuItemImage*>  aLevelIcons);
	cocos2d::CCNode* makeMenuViewWithLevelIcons(std::vector<cocos2d::CCMenuItemImage*>  aLevelIcons);
	cocos2d::CCNode* makeScrollableMenuWithContent(cocos2d::CCNode* aContentContainer);

	void buttonWasPressed(cocos2d::CCObject* pSender);

};

