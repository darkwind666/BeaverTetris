#pragma once

#include "cocos2d.h"

class DetailForTutorialController : public cocos2d::Node
{
public:
	DetailForTutorialController(void);
	~DetailForTutorialController(void);

	cocos2d::Node* getDetailForControllsTutorial();
	cocos2d::FiniteTimeAction* getDetailAppearanceAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getDetailFallenAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getDetailFallenToOneBlockAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getDetailFallenToBossLineAnimation(cocos2d::Node *aDetail);

};

