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
	cocos2d::FiniteTimeAction* getPlayerReduceHorizontalCombinationTutorial();
	cocos2d::FiniteTimeAction* getPlayerReduceVerticalCombinationTutorial();
	cocos2d::FiniteTimeAction* getPlayerUseSpellTutorial();
	cocos2d::FiniteTimeAction* getPlayerFightWithBossTutorial();

private:

	cocos2d::Node* getDetailForControllsTutorial();
	cocos2d::Node* getControllerWithKey(std::string aKey);
	cocos2d::FiniteTimeAction* getDetailAppearanceAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getOperationsOnDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailRightAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getMoveDetailLeftAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getRotateDetailAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getUsePauseButtonAnimation();
	cocos2d::FiniteTimeAction* getMoveDetailDownAnimation(cocos2d::Node *aDetail);
	cocos2d::FiniteTimeAction* getActivateControllerAnimation(cocos2d::Node *aController);

	cocos2d::FiniteTimeAction* getDetailFallenAnimation(cocos2d::Node* aDetail);
	std::vector<cocos2d::Sprite*> getTetraminosInBottom();
	std::vector<cocos2d::Sprite*> getElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex);
	cocos2d::Sprite* getTetraminoViewForType(int aType);
	cocos2d::Vec2 getTetraminoPositionForIndexXY(int xIndex, int yIndex);
	void makeBottomExplosionWithHeight(int aHeight);
	cocos2d::FiniteTimeAction* getTetraminosExplosionAnimationForCallback(std::function<void()> aCallback);
	void setExplosionForIndexXY(int xIndex, int yIndex);
	cocos2d::ParticleSystem* getExplosion();
	std::vector<cocos2d::Node*> getBottomDetailTetraminos(cocos2d::Node* aDetail);
	cocos2d::FiniteTimeAction* getTetraminosDisappearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos);
	cocos2d::FiniteTimeAction* getTetraminosAppearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos);
	cocos2d::FiniteTimeAction* getAnimationWithTetraminosAndDetailAndAction(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos, std::function<cocos2d::FiniteTimeAction*()> action);
	cocos2d::FiniteTimeAction* getAnimationWithTetraminosInDetail(std::vector<cocos2d::Node*> aDetailTetraminos, std::function<cocos2d::FiniteTimeAction*()> action);

	std::vector<cocos2d::Sprite*> getTetraminosHorizontalLineCombination();
	void getHorizontalLineCombinationExplosion();

	cocos2d::FiniteTimeAction* getDetailFallenToOneBlockAnimation(cocos2d::Node *aDetail);
	std::vector<cocos2d::Sprite*> getTetraminosVerticallLineCombination();
	void getVericalLineCombinationExplosion();
	std::vector<cocos2d::Node*> getVerticalDetailTetraminos(cocos2d::Node *aDetail);

	void getSpellExplosion();
	cocos2d::FiniteTimeAction* getUseSpellKeyAnimation();

	cocos2d::FiniteTimeAction* getDetailFallenToBossLineAnimation(cocos2d::Node *aDetail);
	void makeBossEnvironmentTetraminos();
	void makeElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex);
	cocos2d::LabelTTF* getBossLifeCountLabel();
	cocos2d::FiniteTimeAction* getVictoryConditionAnimationWithLifeLabel(cocos2d::LabelTTF *aLabel);
	std::vector<cocos2d::Sprite*> getBossLineTetraminosCombination();

};

