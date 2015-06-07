#include "PlayerScoreForTutorialController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "TutorialConstants.h"

using namespace cocos2d;
using namespace std;

PlayerScoreForTutorialController::PlayerScoreForTutorialController(void)
{
}


PlayerScoreForTutorialController::~PlayerScoreForTutorialController(void)
{
}

LabelTTF* PlayerScoreForTutorialController::getPlayerScoreCountLabel()
{
	LabelTTF *victoryConditionStatus = LabelTTF::create("", "COMIC.TTF", 19);
	victoryConditionStatus->setColor(Color3B(20, 61, 62)); 
	victoryConditionStatus->setString(string("200"));
	return victoryConditionStatus;
}

FiniteTimeAction* PlayerScoreForTutorialController::getPlayerScoreAnimationWithCountLabelAndFinalCount(LabelTTF *aLabel, string aCount)
{
	Sprite *pad = CocosNodesHelper::getSpriteWithKey(playerScoreControllerBackgroundKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(pad, this, gameTutorialPlayerScorePadKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(aLabel, pad, playerScoreControllerCountKey);

	FiniteTimeAction *activateControllerScaleUp = ScaleTo::create(tutorialActionDuration, 1.5f);
	FiniteTimeAction *activateLabel = CallFunc::create([aLabel, aCount](){aLabel->setString(aCount);});
	FiniteTimeAction *activateControllerScaleDown = ScaleTo::create(tutorialActionDuration, 1.0f);
	FiniteTimeAction *sequence = Sequence::create(activateLabel, activateControllerScaleUp, activateControllerScaleDown, nullptr);
	FiniteTimeAction *actionWithCondition = TargetedAction::create(pad, sequence);
	return actionWithCondition;
}