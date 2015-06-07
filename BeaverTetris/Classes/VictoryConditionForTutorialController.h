#pragma once

#include "cocos2d.h"

class VictoryConditionForTutorialController : public cocos2d::Node
{
public:
	VictoryConditionForTutorialController(void);
	~VictoryConditionForTutorialController(void);

	cocos2d::LabelTTF* getBossLifeCountLabel();
	cocos2d::FiniteTimeAction* getVictoryConditionAnimationWithLifeLabel(cocos2d::LabelTTF *aLabel);

};

