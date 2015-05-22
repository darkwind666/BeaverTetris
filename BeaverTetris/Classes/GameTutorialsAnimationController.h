#pragma once 

#include "cocos2d.h"
#include <vector>
#include <functional>

class GameTutorialsAnimationController : public cocos2d::Node
{
public:
	GameTutorialsAnimationController(void);
	~GameTutorialsAnimationController(void);

	cocos2d::FiniteTimeAction* getPlayerControllsTutorial();
	cocos2d::FiniteTimeAction* getPlayerReduceLineTutorial();

private:

	cocos2d::Node* getDetailForControllsTutorial();
	cocos2d::Node* getControllerWithKey(std::string aKey);
	cocos2d::FiniteTimeAction* getDetailAppearanceAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getOperationsOnDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailRightAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailLeftAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getRotateDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailDownAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getActivateControllerAnimation(cocos2d::Node *aController);

	cocos2d::FiniteTimeAction* getDetailFallenAnimation(cocos2d::Node* aDetail);
	std::vector<cocos2d::Sprite*> getTetraminosInBottom();
	std::vector<cocos2d::Sprite*> getElementsFromArray(int *aSourceMassive);
	cocos2d::Sprite* getTetraminoViewForType(int aType);
	cocos2d::Vec2 getTetraminoPositionForIndex(int aIndex);
	cocos2d::FiniteTimeAction* getTetraminosExplosionAnimation();
	void makeBottomExplosion();
	void setExplosionForIndex(int aIndex);
	cocos2d::FiniteTimeAction* getTetraminosDisappearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getTetraminosAppearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getAnimationWithTetraminosAndDetailAndAction(std::vector<cocos2d::Sprite*> aTetraminos, cocos2d::Node *aDetail, std::function<cocos2d::FiniteTimeAction*()> action);

};

