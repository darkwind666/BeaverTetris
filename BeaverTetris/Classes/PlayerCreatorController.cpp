#include "PlayerCreatorController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;
using namespace cocos2d::ui;

PlayerCreatorController::PlayerCreatorController(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_controllerView = getControllerView();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_controllerView, this, playerCreatorControllerPadKey);
}


PlayerCreatorController::~PlayerCreatorController(void)
{
}

Node* PlayerCreatorController::getControllerView()
{   
	Node *createPlayerControllerPad = getPlayerCreatorPad();

	Node *padText = getPlayerCreatorText();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(padText, createPlayerControllerPad, playerCreatorControllerTextKey);

	Node *createPlayerControllerInput = getPlayerCreatorInputHolder();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(createPlayerControllerInput, createPlayerControllerPad, playerCreatorControllerInputKey);

	return createPlayerControllerPad;
}

Node* PlayerCreatorController::getPlayerCreatorPad()
{
	LayerColor *createPlayerControllerPad = LayerColor::create(Color4B::RED, 280, 140);
	createPlayerControllerPad->ignoreAnchorPointForPosition(false);
	return createPlayerControllerPad;
}

Node* PlayerCreatorController::getPlayerCreatorText()
{
	LabelTTF *padText = LabelTTF::create("", "helvetica", 20);
	padText->setString("Enter player name please");
	return padText;
}

Node* PlayerCreatorController::getPlayerCreatorInputHolder()
{
	Scale9Sprite *textBoxImage = Scale9Sprite::create("HelloWorld.png");
	textBoxImage->setScale9Enabled(false);
	textBoxImage->setScaleX(0.4f);
	textBoxImage->setScaleY(0.1f);
	
	CCSize inputBoxSize = textBoxImage->getBoundingBox().size;
	
	EditBox *createPlayerControllerInput = EditBox::create(inputBoxSize,textBoxImage);
	createPlayerControllerInput->setPlaceHolder("Sasha");
	createPlayerControllerInput->setFontName("helvetica");
	createPlayerControllerInput->setFontSize(20);
	createPlayerControllerInput->setDelegate(this);
	return createPlayerControllerInput;
}

void PlayerCreatorController::onEnterTransitionDidFinish()
{

	if (!_currentPlayerDataSource->isThereCurentPlayer())
	{
		_previousPosition = _controllerView->getPosition();
		Vec2 finalActionPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(playerCreatorControllerPadKey);
		ActionInterval *movePad = MoveTo::create(createPlayerControllerAppearDuration, finalActionPosition);
		Action *ease = EaseBackOut::create(movePad);
		_controllerView->runAction(ease);
	}
	else
	{

	}
	
}

void PlayerCreatorController::editBoxReturn(EditBox* editBox)
{
	const char* textStart = editBox->getText();
	_currentPlayerDataSource->setNewPlayerWithName(string(textStart));

	ActionInterval *movePadBack = MoveTo::create(createPlayerControllerDisapperDuration, _previousPosition);
	_controllerView->runAction(movePadBack);
}