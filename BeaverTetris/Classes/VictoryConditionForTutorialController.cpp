#include "VictoryConditionForTutorialController.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "GameFileExtensionMaker.h"
#include "GameViewElementsKeys.h"
#include "TutorialConstants.h"

using namespace cocos2d;
using namespace std;

VictoryConditionForTutorialController::VictoryConditionForTutorialController(void)
{
}


VictoryConditionForTutorialController::~VictoryConditionForTutorialController(void)
{
}

LabelTTF* VictoryConditionForTutorialController::getBossLifeCountLabel()
{
	LabelTTF *victoryConditionStatus = GameViewStyleHelper::getStandardLabel();
	victoryConditionStatus->setFontSize(19.0f);
	victoryConditionStatus->setString(string("1"));
	return victoryConditionStatus;
}

FiniteTimeAction* VictoryConditionForTutorialController::getVictoryConditionAnimationWithLifeLabel(LabelTTF *aLabel)
{
	Sprite *pad = CocosNodesHelper::getSpriteWithKey(victoryConditionPadImageKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(pad, this, gameTutorialVictoryConditionPadKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(aLabel, pad, gameTutorialVictoryConditionCountLabelKey);

	string bossImageName = GameFileExtensionMaker::getGraphicWithExtension("queenBossWinConditionIcon");
	Sprite *bossImage = Sprite::createWithSpriteFrameName(bossImageName);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(bossImage, pad, gameTutorialVictoryConditionImageKey);

	FiniteTimeAction *activateControllerScaleUp = ScaleTo::create(tutorialActionDuration, 1.5f);
	FiniteTimeAction *activateLabel = CallFunc::create([aLabel](){aLabel->setString(string("0"));});
	FiniteTimeAction *activateControllerScaleDown = ScaleTo::create(tutorialActionDuration, 1.0f);
	FiniteTimeAction *sequence = Sequence::create(activateLabel, activateControllerScaleUp, activateControllerScaleDown, nullptr);
	FiniteTimeAction *actionWithCondition = TargetedAction::create(pad, sequence);
	return actionWithCondition;
}
