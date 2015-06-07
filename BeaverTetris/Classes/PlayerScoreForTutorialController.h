#pragma once

#include "cocos2d.h"
#include <string>

class PlayerScoreForTutorialController : public cocos2d::Node
{
public:
	PlayerScoreForTutorialController(void);
	~PlayerScoreForTutorialController(void);

	cocos2d::LabelTTF* getPlayerScoreCountLabel();
	cocos2d::FiniteTimeAction* getPlayerScoreAnimationWithCountLabelAndFinalCount(cocos2d::LabelTTF *aLabel, std::string aCount);

};

