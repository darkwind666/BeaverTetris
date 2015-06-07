#pragma once

#include "cocos2d.h"

class PlayerActionsForTutorialController : public cocos2d::Node
{
public:
	PlayerActionsForTutorialController(void);
	~PlayerActionsForTutorialController(void);

	cocos2d::FiniteTimeAction* getOperationsOnDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::Node* getControllerWithKey(std::string aKey);
	cocos2d::FiniteTimeAction* getActivateControllerAnimation(cocos2d::Node *aController);
	cocos2d::FiniteTimeAction* getUseSpellKeyAnimation();
	cocos2d::FiniteTimeAction* getUseSpellButtonAnimationWithKey(std::string aKey);

private:

	cocos2d::FiniteTimeAction* getMoveDetailRightAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailLeftAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getRotateDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getUsePauseButtonAnimation();
	cocos2d::FiniteTimeAction* getMoveDetailDownAnimation(cocos2d::Node *aDetail);

};

