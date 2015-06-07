#include "DetailForTutorialController.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "CocosNodesHelper.h"
#include "TutorialConstants.h"

using namespace cocos2d;

DetailForTutorialController::DetailForTutorialController(void)
{
}


DetailForTutorialController::~DetailForTutorialController(void)
{
}

Node* DetailForTutorialController::getDetailForControllsTutorial()
{
	Node *detailPad = Node::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(detailPad, this, gameTutorialStartDetailKey);

	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);

	string teraminoImageName = GameFileExtensionMaker::getGraphicWithExtension(redTetraminoKey);
	Sprite *tetramino1 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino1->setPosition(Vec2(0, 0));
	tetramino1->setTag(tetramino1Tag);
	Sprite *tetramino2 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino2->setPosition(Vec2(0, tetraminoOffset.y));
	tetramino2->setTag(tetramino2Tag);
	Sprite *tetramino3 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino3->setPosition(Vec2(0, -tetraminoOffset.y));
	tetramino3->setTag(tetramino3Tag);
	Sprite *tetramino4 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino4->setPosition(Vec2(tetraminoOffset.x, tetraminoOffset.y));
	tetramino4->setTag(tetramino4Tag);

	detailPad->addChild(tetramino1);
	detailPad->addChild(tetramino2);
	detailPad->addChild(tetramino3);
	detailPad->addChild(tetramino4);

	return detailPad;
}

FiniteTimeAction* DetailForTutorialController::getDetailAppearanceAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(tutorialActionDuration, finalPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

FiniteTimeAction* DetailForTutorialController::getDetailFallenAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(0.6f, finalPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

FiniteTimeAction* DetailForTutorialController::getDetailFallenToOneBlockAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 detailPosition = Vec2(finalPosition.x, finalPosition.y + offset.y);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(0.6f,  detailPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

FiniteTimeAction* DetailForTutorialController::getDetailFallenToBossLineAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 detailPosition = Vec2(finalPosition.x, finalPosition.y + offset.y * 3);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(0.6f,  detailPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}