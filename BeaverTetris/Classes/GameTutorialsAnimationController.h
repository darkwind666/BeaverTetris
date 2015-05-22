#pragma once 

#include "cocos2d.h"

class GameTutorialsAnimationController : public cocos2d::Node
{
public:
	GameTutorialsAnimationController(void);
	~GameTutorialsAnimationController(void);

	cocos2d::FiniteTimeAction* getPlayerControllsTutorial();

private:

	cocos2d::Node* getDetailForControllsTutorial();
	cocos2d::Node* getControllerWithKey(std::string aKey);
	cocos2d::FiniteTimeAction* getDetailAppearanceAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getOperationsOnDetailAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailRightAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailLeftAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getRotateDetailAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailDownAnimation(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getActivateControllerAnimation(cocos2d::Node* aController);

};

