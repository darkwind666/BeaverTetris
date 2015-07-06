#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"

#include "GameStatesHelper.h"
#include "GameEnums.h"
#include "GameKeyWithSuffixSupporter.h"
#include "MouseOverMenuItem.h"
#include "StringsSupporter.h"
#include "GameLocalizationKeys.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewElementsDataSource.h"

using namespace std;
using namespace cocos2d;

GameViewStyleHelper::GameViewStyleHelper(void)
{
}


GameViewStyleHelper::~GameViewStyleHelper(void)
{
}


void GameViewStyleHelper::runStandardButtonActionWithCallback(Node *aButton, function<void()> aCallback)
{
	runButtonActionWithCallbackAndDuration(aButton, aCallback, standardButtonActionDuration);
}

void GameViewStyleHelper::runButtonActionWithCallbackAndDuration(Node *aButton, function<void()> aCallback, float aDuration)
{
	FiniteTimeAction *playSoundAction = getSoundActionWithKey(buttonPressedSoundKey);
	FiniteTimeAction *scaleOut = ScaleTo::create(aDuration, aButton->getScaleX() * standardButtonScaleForAction , aButton->getScaleY() * standardButtonScaleForAction);
	FiniteTimeAction *scaleIn = ScaleTo::create(aDuration, aButton->getScaleX(), aButton->getScaleY());
	FiniteTimeAction *callback = CallFunc::create(aCallback);
	Sequence *sequence = Sequence::create(playSoundAction, scaleOut, scaleIn, callback, NULL);
	aButton->runAction(sequence);
}

FiniteTimeAction* GameViewStyleHelper::getSoundActionWithKey(string aKey)
{
	FiniteTimeAction *playSoundAction = CallFunc::create([aKey](){
		string pressButtonSoundEffect = GameFileExtensionMaker::getSoundWithExtension(aKey);
		GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
		gameSoundController->playSoundEffectForKey(pressButtonSoundEffect);
	});
	return playSoundAction;
}

LabelTTF* GameViewStyleHelper::getStandardLabel()
{
	return LabelTTF::create("", "COMIC.TTF", 15);
}

cocos2d::Label* GameViewStyleHelper::getStandardLabelWithFontSize(float aFontSize)
{
	return Label::createWithTTF("", "Schist Black.TTF", aFontSize);
}

void GameViewStyleHelper::addBackButtonToParentNodeWithKey(Node *aParentNode, string aKey)
{
	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};
	addBackButtonToParentNodeWithKeyAndCallback(aParentNode, aKey, callback);
}

void GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallback(Node *aParentNode, string aKey, ccMenuCallback aCallback)
{
	addBackButtonToParentNodeWithKeyAndCallbackAndLocalization(aParentNode, aKey, aCallback, gameBackButtonLocalizationKey);
}

void GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallbackAndLocalization(Node *aParentNode, string aKey, ccMenuCallback aCallback, string aLocale)
{
	MenuItem *closeButton = getCloseButtonWithKeyAndCallbackAndLocalization(aKey, aCallback, aLocale);
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButton,aParentNode,aKey);
}

MenuItem* GameViewStyleHelper::getCloseButtonWithKeyAndCallbackAndLocalization(string aKey, ccMenuCallback aCallback, string aLocale)
{
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	string buttonImageKey = gameViewElementsDataSource->getElementImageForKey(aKey);
	string inactiveImageName = GameKeyWithSuffixSupporter::makeUnselectedImageForKey(buttonImageKey);
	string activeImageName = GameKeyWithSuffixSupporter::makeSelectedImageForKey(buttonImageKey);
	MouseOverMenuItem *closeButtonItem = new MouseOverMenuItem(activeImageName,inactiveImageName,aCallback);
	
	Label *backButtonText = GameViewStyleHelper::getStandardLabelWithFontSize(18.0f);
	backButtonText->setString(StringsSupporter::getLocalizedStringFromKey(aLocale));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backButtonText, closeButtonItem, closeButtonTextKey);
	
	return closeButtonItem;
}

void GameViewStyleHelper::addPopUpBackgroundToParentNodeWithKey(Node *aParentNode, string aKey)
{
	Node *background = getPopUpBackground();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background, aParentNode, aKey);
}

Node* GameViewStyleHelper::getPopUpBackground()
{
	float width = Director::getInstance()->getWinSizeInPixels().width;
	float height = Director::getInstance()->getWinSizeInPixels().height;
	LayerColor *background = LayerColor::create(Color4B(93, 176, 192, 200), width, height);
	background->ignoreAnchorPointForPosition(false);
	return background;
}
