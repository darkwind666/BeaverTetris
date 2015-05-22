#include "GameTutorialsAnimationController.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameDesignConstants.h"
#include "CocosNodesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"

using namespace cocos2d;

const float tutorialActionDuration = 0.3f;

GameTutorialsAnimationController::GameTutorialsAnimationController(void)
{
}


GameTutorialsAnimationController::~GameTutorialsAnimationController(void)
{
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerControllsTutorial()
{
	Node *detail = getDetailForControllsTutorial();

	FiniteTimeAction *detailAppearanceAnimation = getDetailAppearanceAnimation(detail);
	FiniteTimeAction *operationsOnDetailAnimation = getOperationsOnDetailAnimation(detail);

	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);

	FiniteTimeAction *setStartAngle = CallFunc::create([detail](){detail->setRotation(90);});
	FiniteTimeAction *actionWithRotateDetailAtStartEngle = TargetedAction::create(detail, setStartAngle);

	ActionInterval *sequence  = Sequence::create(detailAppearanceAnimation, operationsOnDetailAnimation, actionWithMoveDetailAtStartPositon, actionWithRotateDetailAtStartEngle, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

Node* GameTutorialsAnimationController::getDetailForControllsTutorial()
{
	Node *detailPad = Node::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(detailPad, this, gameTutorialStartDetailKey);

	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);

	string teraminoImageName = GameFileExtensionMaker::getGraphicWithExtension(redTetraminoKey);
	Sprite *tetramino1 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino1->setPosition(Vec2(0, 0));
	Sprite *tetramino2 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino2->setPosition(Vec2(0, tetraminoOffset.y));
	Sprite *tetramino3 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino3->setPosition(Vec2(0, -tetraminoOffset.y));
	Sprite *tetramino4 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino4->setPosition(Vec2(tetraminoOffset.x, tetraminoOffset.y));

	detailPad->addChild(tetramino1);
	detailPad->addChild(tetramino2);
	detailPad->addChild(tetramino3);
	detailPad->addChild(tetramino4);

	return detailPad;
}

FiniteTimeAction* GameTutorialsAnimationController::getDetailAppearanceAnimation(Node* aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(tutorialActionDuration, finalPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

FiniteTimeAction* GameTutorialsAnimationController::getOperationsOnDetailAnimation(Node* aDetail)
{
	FiniteTimeAction *moveDetailRightAnimation = getMoveDetailRightAnimation(aDetail);
	FiniteTimeAction *moveDetailLeftAnimation = getMoveDetailLeftAnimation(aDetail);
	FiniteTimeAction *rotateDetailAnimation = getRotateDetailAnimation(aDetail);
	FiniteTimeAction *moveDetailDownAnimation = getMoveDetailDownAnimation(aDetail);
	FiniteTimeAction *sequence = Sequence::create(moveDetailRightAnimation, moveDetailLeftAnimation, rotateDetailAnimation, moveDetailDownAnimation, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailRightAnimation(Node* aDetail)
{
	Node *rightController = getControllerWithKey(gameTutorialMoveDetailRightControlKey);
	FiniteTimeAction *actionWithRightController = getActivateControllerAnimation(rightController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailRight = MoveBy::create(tutorialActionDuration, Vec2(offset.x, 0));
	FiniteTimeAction *actionWithRightDetailDirection = TargetedAction::create(aDetail, moveDetailRight);
	FiniteTimeAction *sequence = Sequence::create(actionWithRightController, actionWithRightDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailLeftAnimation(Node* aDetail)
{
	Node *leftController = getControllerWithKey(gameTutorialMoveDetailLeftControlKey);
	FiniteTimeAction *actionWithLeftController = getActivateControllerAnimation(leftController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailLeft = MoveBy::create(tutorialActionDuration, Vec2(-offset.x, 0));
	FiniteTimeAction *actionWithLeftDetailDirection = TargetedAction::create(aDetail, moveDetailLeft);
	FiniteTimeAction *sequence = Sequence::create(actionWithLeftController, actionWithLeftDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getRotateDetailAnimation(Node* aDetail)
{
	Node *upController = getControllerWithKey(gameTutorialRotateDetailControlKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(upController);
	FiniteTimeAction *rotateDetail = RotateTo::create(tutorialActionDuration, 180.0f);
	FiniteTimeAction *actionWithRotateDetail = TargetedAction::create(aDetail, rotateDetail);
	FiniteTimeAction *sequence = Sequence::create(actionWithUpController, actionWithRotateDetail, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailDownAnimation(Node* aDetail)
{
	Node *downController = getControllerWithKey(gameTutorialAccelerateDetailControlKey);
	FiniteTimeAction *actionWithDownController = getActivateControllerAnimation(downController);
	Vec2 detailDownPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailDown = MoveTo::create(tutorialActionDuration, detailDownPosition);
	FiniteTimeAction *actionWithMoveDetailDown = TargetedAction::create(aDetail, moveDetailDown);
	FiniteTimeAction *delay = DelayTime::create(tutorialActionDuration);
	FiniteTimeAction *sequence = Sequence::create(actionWithDownController, actionWithMoveDetailDown, delay, nullptr);
	return sequence;
}

Node* GameTutorialsAnimationController::getControllerWithKey(string aKey)
{
	Sprite *controllerView = CocosNodesHelper::getSpriteWithKey(playerControlActiveImageKey);
	controllerView->setScale(2.0f);
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 controllerPosition = gameViewElementsDataSource->getElementPositionForKey(aKey);
	controllerView->setPosition(controllerPosition);
	Vec2 controllRotation = gameViewElementsDataSource->getElementOffsetForKey(aKey);
	controllerView->setRotation(controllRotation.x);
	this->addChild(controllerView);
	return controllerView;
}

FiniteTimeAction* GameTutorialsAnimationController::getActivateControllerAnimation(Node* aController)
{
	float startScale = aController->getScale();
	FiniteTimeAction *activateControllerScaleDown = ScaleTo::create(tutorialActionDuration, 1.0f);
	FiniteTimeAction *activateControllerScaleUp = ScaleTo::create(tutorialActionDuration, startScale);
	FiniteTimeAction *sequence = Sequence::create(activateControllerScaleDown, activateControllerScaleUp, nullptr);
	FiniteTimeAction *actionWithController = TargetedAction::create(aController, sequence);
	return actionWithController;
}

