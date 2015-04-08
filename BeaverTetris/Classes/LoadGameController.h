#pragma once

#include "cocos2d.h"

class LoadingGameDataSource;

class LoadGameController : public cocos2d::Node
{
public:
	LoadGameController(void);
	~LoadGameController(void);

	virtual void onEnterTransitionDidFinish(); 

private:

	cocos2d::ProgressTimer *_loadGameControllerView;
	LoadingGameDataSource *_loadingGameDataSource;
	int _loadedResourcesCount;

	void loadGameResource();
	void loadOneResource();
	void runLoadingActionWithLoadingPercent(int aLoadingPercent);

};

