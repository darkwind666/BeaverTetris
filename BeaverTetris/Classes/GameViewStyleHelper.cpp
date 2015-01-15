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


void GameViewStyleHelper::runStandardButtonActionWithCallback(CCNode *aButton, function<void()> aCallback)
{
	CCActionInterval *scaleOut = CCScaleTo::create(standardButtonActionDuration, aButton->getScaleX() * standardButtonScaleForAction , aButton->getScaleY() * standardButtonScaleForAction);
	CCActionInterval *scaleIn = CCScaleTo::create(standardButtonActionDuration, aButton->getScaleX(), aButton->getScaleY());
	CCCallFunc *callback = CCCallFunc::create(aCallback);
	CCSequence *sequence = CCSequence::create(scaleOut, scaleIn, callback, NULL);
	aButton->runAction(sequence);
}