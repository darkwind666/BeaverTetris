#pragma once

#include "cocos2d.h"

class LoadingGameDataSource;

class LoadGameController : public cocos2d::CCNode
{
public:
	LoadGameController(void);
	~LoadGameController(void);

	virtual void onEnterTransitionDidFinish(); 

private:

	cocos2d::CCProgressTimer *_loadGameControllerView;
	LoadingGameDataSource *_loadingGameDataSource;
	int _loadedResourcesCount;

	void loadGameResource();
	void loadOneResource();
	void runLoadingActionWithLoadingPercent(int aLoadingPercent);

};

