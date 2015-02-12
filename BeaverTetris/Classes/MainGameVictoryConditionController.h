#pragma once

#include "cocos2d.h"
#include "GameStructures.h"
#include <vector>

class VictoryConditionViewDataSource;

class MainGameVictoryConditionController : public cocos2d::Node
{
public:
	MainGameVictoryConditionController(void);
	~MainGameVictoryConditionController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);

private:

	VictoryConditionViewDataSource *_victoryConditionViewDataSource;
	std::vector<VictoryConditionViewElements> _viewElements;

	std::vector<VictoryConditionViewElements> makeViewElements();
	cocos2d::Sprite* getVictoryConditionImageViewForIndex(int aConditionIndex);
	cocos2d::LabelTTF* getVictoryConditionStatusViewForIndex(int aConditionIndex);
	void addViewElements(std::vector<VictoryConditionViewElements> aViewElements);
	void cleanViews();
	void updateViews();

};

