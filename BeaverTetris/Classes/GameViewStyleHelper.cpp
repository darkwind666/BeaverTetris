#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"
#include "SimpleAudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

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
		SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
		audioEngine->playEffect(pressButtonSoundEffect.c_str());
	});
	return playSoundAction;
}

LabelTTF* GameViewStyleHelper::getStandardLabel()
{
	return LabelTTF::create("", "Helvetica", 120);
}
