#include "PlayerCreatorController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"
#include "PlayerStatusDelegateInterface.h"
#include "GameFileExtensionMaker.h"

#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"
#include "GameKeyWithSuffixSupporter.h"
#include "MouseOverMenuItem.h"

using namespace cocos2d;
using namespace cocos2d::ui;

PlayerCreatorController::PlayerCreatorController(void)
{
	_delegate = NULL;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_controllerView = getControllerView();

	CocosNodesHelper::addSpriteToParentNodeWithKey(this, playerCreatorControllerBackgroundKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_controllerView, this, playerCreatorControllerPadKey);
	this->setVisible(false);
}


PlayerCreatorController::~PlayerCreatorController(void)
{
}

Node* PlayerCreatorController::getControllerView()
{   
	Node *createPlayerControllerPad = CocosNodesHelper::getSpriteWithKey(playerCreatorControllerPadKey);

	Node *padText = getPlayerCreatorText();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(padText, createPlayerControllerPad, playerCreatorControllerTextKey);

	Node *createPlayerControllerInput = getPlayerCreatorInputHolder();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(createPlayerControllerInput, createPlayerControllerPad, playerCreatorControllerInputKey);

	MenuItem *closeButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButton,createPlayerControllerPad,playerCreatorControllerBackButtonKey);

	return createPlayerControllerPad;
}

Node* PlayerCreatorController::getPlayerCreatorText()
{
	LabelTTF *padText = GameViewStyleHelper::getStandardLabel();
	padText->setColor(Color3B(89,72,52));
	padText->setString("Enter player name please");
	return padText;
}

Node* PlayerCreatorController::getPlayerCreatorInputHolder()
{
	string textInputImage = GameFileExtensionMaker::getGraphicWithExtension(playerCreatorControllerInputKey);
	Scale9Sprite *textBoxImage = Scale9Sprite::createWithSpriteFrameName(textInputImage);
	textBoxImage->setScale9Enabled(false);
	
	Size inputBoxSize = textBoxImage->getBoundingBox().size;
	
	EditBox *createPlayerControllerInput = EditBox::create(inputBoxSize,textBoxImage);
	createPlayerControllerInput->setPlaceHolder("");
	createPlayerControllerInput->setDelegate(this);
	return createPlayerControllerInput;
}

MenuItem* PlayerCreatorController::getCloseButton()
{
	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};

	string inactiveImageName = GameKeyWithSuffixSupporter::makeUnselectedImageForKey(playerCreatorControllerBackButtonKey);
	string activeImageName = GameKeyWithSuffixSupporter::makeSelectedImageForKey(playerCreatorControllerBackButtonKey);
	MouseOverMenuItem *closeButtonItem = new MouseOverMenuItem(activeImageName,inactiveImageName,callback);
	return closeButtonItem;
}

void PlayerCreatorController::onEnterTransitionDidFinish()
{
	if (_currentPlayerDataSource->isThereCurentPlayer() == false)
	{
		this->setVisible(true);
	}
	else
	{
		invokeDelegate();
	}
}

void PlayerCreatorController::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    const char* textStart = editBox->getText();
	_currentPlayerDataSource->setNewPlayerWithName(string(textStart));
	this->setVisible(false);
	FiniteTimeAction *callback = CallFunc::create([this](){invokeDelegate();});
	_controllerView->runAction(callback);
}

void PlayerCreatorController::editBoxReturn(ui::EditBox* editBox)
{
}

void PlayerCreatorController::setDelegate(PlayerStatusDelegateInterface *aDelegate)
{
	_delegate = aDelegate;
}

void PlayerCreatorController::invokeDelegate()
{
	if (_delegate)
	{
		_delegate->showPlayerStatus();
	}
}

