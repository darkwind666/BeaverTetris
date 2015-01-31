#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"

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
	ActionInterval *scaleOut = ScaleTo::create(standardButtonActionDuration, aButton->getScaleX() * standardButtonScaleForAction , aButton->getScaleY() * standardButtonScaleForAction);
	ActionInterval *scaleIn = ScaleTo::create(standardButtonActionDuration, aButton->getScaleX(), aButton->getScaleY());
	CallFunc *callback = CallFunc::create(aCallback);
	Sequence *sequence = Sequence::create(scaleOut, scaleIn, callback, NULL);
	aButton->runAction(sequence);
}

LabelTTF* GameViewStyleHelper::getStandardLabel()
{
	return LabelTTF::create("", "Helvetica", 120);
}
