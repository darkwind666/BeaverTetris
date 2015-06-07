#pragma once

#include "cocos2d.h"
#include <vector>
#include <functional>

class TetraminosForTutorialController : public cocos2d::Node
{
public:
	TetraminosForTutorialController(void);
	~TetraminosForTutorialController(void);

	std::vector<cocos2d::Sprite*> getTetraminosInBottom();
	cocos2d::Vec2 getTetraminoPositionForIndexXY(int xIndex, int yIndex);
	std::vector<cocos2d::Sprite*> getElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex);
	std::vector<cocos2d::Node*> getBottomDetailTetraminos(cocos2d::Node* aDetail);
	std::vector<cocos2d::Node*> getVerticalDetailTetraminos(cocos2d::Node *aDetail);
	std::vector<cocos2d::Sprite*> getTetraminosHorizontalLineCombination();
	std::vector<cocos2d::Sprite*> getTetraminosVerticallLineCombination();
	void makeBossEnvironmentTetraminos();
	void makeElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex);
	std::vector<cocos2d::Sprite*> getBossLineTetraminosCombination();
	std::vector<cocos2d::Sprite*> getTetraminosForRandomExplosions();
	std::vector<cocos2d::Sprite*>  getTetraminosForFirestorm();
	std::vector<cocos2d::Sprite*> getTetraminosForCohesion();
	std::vector<cocos2d::Node*> getCohesionTetraminos();

	cocos2d::FiniteTimeAction* getTetraminosDisappearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos);
	cocos2d::FiniteTimeAction* getTetraminosAppearanceAnimation(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos);
	cocos2d::FiniteTimeAction* getCohesionAnimationWithTetraminos(std::vector<cocos2d::Node*> aTetraminos);
	

private:

	cocos2d::Sprite* getTetraminoViewForType(int aType);
	cocos2d::FiniteTimeAction* getAnimationWithTetraminosAndDetailAndAction(std::vector<cocos2d::Sprite*> aTetraminos, std::vector<cocos2d::Node*> aDetailTetraminos, std::function<cocos2d::FiniteTimeAction*()> action);
	cocos2d::FiniteTimeAction* getTetraminosSequenceWithAction(std::vector<cocos2d::Sprite*> aTetraminos, std::function<cocos2d::FiniteTimeAction*()> action);
	cocos2d::FiniteTimeAction* getAnimationInDetailWithTetraminosSequenceAndAction(std::vector<cocos2d::Node*> aDetailTetraminos, cocos2d::FiniteTimeAction* aTetraminosSequence, std::function<cocos2d::FiniteTimeAction*()> action);
	cocos2d::FiniteTimeAction* getAnimationWithTetraminosInDetail(std::vector<cocos2d::Node*> aDetailTetraminos, std::function<cocos2d::FiniteTimeAction*()> action);
	void addCohessionAnimation(cocos2d::Node *aView, cocos2d::Vector<cocos2d::FiniteTimeAction*> *actions);

};

