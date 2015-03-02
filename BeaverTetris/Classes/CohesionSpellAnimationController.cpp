#include "CohesionSpellAnimationController.h"
#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CohesionSpell.h"
#include "TetraminosAppearanceAnimationFactory.h"

using namespace cocos2d;

CohesionSpellAnimationController::CohesionSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_tetraminosAppearanceAnimationFactory = new TetraminosAppearanceAnimationFactory(aGameBoardController);
	this->addChild(_tetraminosAppearanceAnimationFactory);

	CohesionSpell *cohesionSpellModel = (CohesionSpell*)ServiceLocator::getServiceForKey(cohesionSpellModelKey);
	cohesionSpellModel->setDelegate(this);

}


CohesionSpellAnimationController::~CohesionSpellAnimationController(void)
{
}

void CohesionSpellAnimationController::makeTetraminoOnPosition(GamePositionOnBoard aPosition)
{
	FiniteTimeAction *animationWithTetraminoView = _tetraminosAppearanceAnimationFactory->getAnimationWithTetraminoPosition(aPosition);
	_animationSynchonizer->addAnimationToQueue(animationWithTetraminoView);
}
