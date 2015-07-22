#include "PlayerActionsForTutorialController.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "CocosNodesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "GameAnimationActionsConstants.h"
#include "TutorialConstants.h"

using namespace cocos2d;

PlayerActionsForTutorialController::PlayerActionsForTutorialController(void)
{
}


PlayerActionsForTutorialController::~PlayerActionsForTutorialController(void)
{
}

FiniteTimeAction* PlayerActionsForTutorialController::getOperationsOnDetailAnimation(Node *aDetail)
{
	FiniteTimeAction *moveDetailRightAnimation = getMoveDetailRightAnimation(aDetail);
	FiniteTimeAction *moveDetailLeftAnimation = getMoveDetailLeftAnimation(aDetail);
	FiniteTimeAction *rotateDetailAnimation = getRotateDetailAnimation(aDetail);
	FiniteTimeAction *usePauseButtonAnimation = getUsePauseButtonAnimation();
	FiniteTimeAction *moveDetailDownAnimation = getMoveDetailDownAnimation(aDetail);
	FiniteTimeAction *sequence = Sequence::create(moveDetailRightAnimation, moveDetailLeftAnimation, rotateDetailAnimation, usePauseButtonAnimation, moveDetailDownAnimation, nullptr);
	return sequence;
}

FiniteTimeAction* PlayerActionsForTutorialController::getMoveDetailRightAnimation(Node *aDetail)
{
	Node *rightController = getControllerWithKey(gameTutorialMoveDetailRightControlKey);
	FiniteTimeAction *actionWithRightController = getActivateControllerAnimation(rightController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailRight = MoveBy::create(tutorialActionDuration, Vec2(offset.x, 0));
	FiniteTimeAction *actionWithRightDetailDirection = TargetedAction::create(aDetail, moveDetailRight);
	FiniteTimeAction *sequence = Sequence::create(actionWithRightController, actionWithRightDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* PlayerActionsForTutorialController::getMoveDetailLeftAnimation(Node *aDetail)
{
	Node *leftController = getControllerWithKey(gameTutorialMoveDetailLeftControlKey);
	FiniteTimeAction *actionWithLeftController = getActivateControllerAnimation(leftController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailLeft = MoveBy::create(tutorialActionDuration, Vec2(-offset.x, 0));
	FiniteTimeAction *actionWithLeftDetailDirection = TargetedAction::create(aDetail, moveDetailLeft);
	FiniteTimeAction *sequence = Sequence::create(actionWithLeftController, actionWithLeftDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* PlayerActionsForTutorialController::getRotateDetailAnimation(Node *aDetail)
{
	Node *upController = getControllerWithKey(gameTutorialRotateDetailControlKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(upController);
	FiniteTimeAction *rotateDetail = RotateTo::create(tutorialActionDuration, 180.0f);
	FiniteTimeAction *actionWithRotateDetail = TargetedAction::create(aDetail, rotateDetail);
	FiniteTimeAction *sequence = Sequence::create(actionWithUpController, actionWithRotateDetail, nullptr);
	return sequence;
}


FiniteTimeAction* PlayerActionsForTutorialController::getUsePauseButtonAnimation()
{
	Node *pauseButton = CocosNodesHelper::getSpriteWithKey(gameTutorialUsePauseButtonKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(pauseButton, this, gameTutorialUsePauseButtonKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(pauseButton);
	return actionWithUpController;
}

FiniteTimeAction* PlayerActionsForTutorialController::getMoveDetailDownAnimation(Node *aDetail)
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


Node* PlayerActionsForTutorialController::getControllerWithKey(string aKey)
{
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	string controllerImage = gameViewElementsDataSource->getElementImageForKey(aKey);
	Sprite *controllerView = Sprite::createWithSpriteFrameName(controllerImage);
	Vec2 controllerPosition = gameViewElementsDataSource->getElementPositionForKey(aKey);
	controllerView->setPosition(controllerPosition);
	this->addChild(controllerView);
	return controllerView;
}

FiniteTimeAction* PlayerActionsForTutorialController::getActivateControllerAnimation(Node *aController)
{
	float startScale = aController->getScale();
	FiniteTimeAction *activateControllerScaleDown = ScaleTo::create(tutorialActionDuration, startScale / 2);
	FiniteTimeAction *activateControllerScaleUp = ScaleTo::create(tutorialActionDuration, startScale);
	FiniteTimeAction *sequence = Sequence::create(activateControllerScaleDown, activateControllerScaleUp, nullptr);
	FiniteTimeAction *actionWithController = TargetedAction::create(aController, sequence);
	return actionWithController;
}

FiniteTimeAction* PlayerActionsForTutorialController::getUseSpellKeyAnimation()
{
	FiniteTimeAction *actionWithUpController = getUseSpellButtonAnimationWithKey(gameTutorialUseRocketSpellControlKey);
	ParticleSystem *rocket = ParticleMeteor::create();
	rocket->setGravity(Vec2(200,200));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(rocket, this, gameTutorialUseSpellRocketKey);
	Vec2 rocketFinalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialUseSpellRocketKey);
	FiniteTimeAction *moveRocket = MoveTo::create(0.3f, rocketFinalPosition);
	FiniteTimeAction *setStartRocketPosition = Place::create(rocket->getPosition());
	FiniteTimeAction *rocketSequence = Sequence::create(moveRocket, setStartRocketPosition, nullptr);
	FiniteTimeAction *animationWithRocket = TargetedAction::create(rocket, rocketSequence);

	FiniteTimeAction *sequence = Sequence::create(actionWithUpController, animationWithRocket, nullptr);
	return sequence;
}

FiniteTimeAction* PlayerActionsForTutorialController::getUseSpellButtonAnimationWithKey(string aKey)
{
	Sprite *spellButton = CocosNodesHelper::getSpriteWithKey(aKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(spellButton, this, aKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(spellButton);
	return actionWithUpController;
}