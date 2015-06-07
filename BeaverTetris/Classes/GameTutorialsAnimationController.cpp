#include "GameTutorialsAnimationController.h"
#include "GameViewElementsKeys.h"

#include "DetailForTutorialController.h"
#include "PlayerActionsForTutorialController.h"
#include "PlayerScoreForTutorialController.h"
#include "TetraminosForTutorialController.h"
#include "ExplosionsForTutorialController.h"
#include "VictoryConditionForTutorialController.h"
#include "TutorialConstants.h"

using namespace cocos2d;
using namespace std;

GameTutorialsAnimationController::GameTutorialsAnimationController(void)
{
	DetailForTutorialController *detailController = new DetailForTutorialController();
	_detailController = detailController;
	this->addChild(detailController);

	PlayerActionsForTutorialController *playerActionsController = new PlayerActionsForTutorialController();
	_playerActionsController = playerActionsController;
	this->addChild(playerActionsController);

	PlayerScoreForTutorialController *scoreController = new PlayerScoreForTutorialController();
	_scoreController = scoreController;
	this->addChild(scoreController);

	TetraminosForTutorialController *tetraminosController = new TetraminosForTutorialController();
	_tetraminosController = tetraminosController;
	this->addChild(tetraminosController);

	ExplosionsForTutorialController *explosionsController = new ExplosionsForTutorialController();
	_explosionsController = explosionsController;
	this->addChild(explosionsController);

	VictoryConditionForTutorialController *victoryConditionController = new VictoryConditionForTutorialController();
	_victoryConditionController = victoryConditionController;
	this->addChild(victoryConditionController);

}


GameTutorialsAnimationController::~GameTutorialsAnimationController(void)
{
}

void GameTutorialsAnimationController::cleanCurrentTutorial()
{
	this->stopAllActions();
	_detailController->removeAllChildrenWithCleanup(true);
	_playerActionsController->removeAllChildrenWithCleanup(true);
	_scoreController->removeAllChildrenWithCleanup(true);
	_tetraminosController->removeAllChildrenWithCleanup(true);
	_explosionsController->removeAllChildrenWithCleanup(true);
	_victoryConditionController->removeAllChildrenWithCleanup(true);
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerControllsTutorial()
{
	Node *detail = _detailController->getDetailForControllsTutorial();

	FiniteTimeAction *detailAppearanceAnimation = _detailController->getDetailAppearanceAnimation(detail);
	FiniteTimeAction *operationsOnDetailAnimation = _playerActionsController->getOperationsOnDetailAnimation(detail);

	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);

	FiniteTimeAction *setStartAngle = CallFunc::create([detail](){detail->setRotation(90);});
	FiniteTimeAction *actionWithRotateDetailAtStartEngle = TargetedAction::create(detail, setStartAngle);

	ActionInterval *sequence  = Sequence::create(detailAppearanceAnimation, operationsOnDetailAnimation, actionWithMoveDetailAtStartPositon, actionWithRotateDetailAtStartEngle, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceLineTutorial()
{
	LabelTTF *playerScoreCount = _scoreController->getPlayerScoreCountLabel();
	FiniteTimeAction *playerScoreAnimation = _scoreController->getPlayerScoreAnimationWithCountLabelAndFinalCount(playerScoreCount, string("300"));
	FiniteTimeAction *playerScoreStartAnimation = CallFunc::create([playerScoreCount](){playerScoreCount->setString(string("200"));});

	Node *detail = _detailController->getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = _detailController->getDetailFallenAnimation(detail);
	vector<Sprite*> tetraminosInBottom = _tetraminosController->getTetraminosInBottom();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->makeBottomExplosionWithHeight(1);});
	vector<Node*> detailTetraminos = _tetraminosController->getBottomDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, playerScoreAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, playerScoreStartAnimation, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceHorizontalCombinationTutorial()
{
	LabelTTF *playerScoreCount = _scoreController->getPlayerScoreCountLabel();
	FiniteTimeAction *playerScoreAnimation = _scoreController->getPlayerScoreAnimationWithCountLabelAndFinalCount(playerScoreCount, string("300"));
	FiniteTimeAction *playerScoreStartAnimation = CallFunc::create([playerScoreCount](){playerScoreCount->setString(string("200"));});

	Node *detail = _detailController->getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = _detailController->getDetailFallenAnimation(detail);
	vector<Sprite*> tetraminosInBottom = _tetraminosController->getTetraminosHorizontalLineCombination();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->getHorizontalLineCombinationExplosion();});
	vector<Node*> detailTetraminos = _tetraminosController->getBottomDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, playerScoreAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, playerScoreStartAnimation, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceVerticalCombinationTutorial()
{

	LabelTTF *playerScoreCount = _scoreController->getPlayerScoreCountLabel();
	FiniteTimeAction *playerScoreAnimation = _scoreController->getPlayerScoreAnimationWithCountLabelAndFinalCount(playerScoreCount, string("300"));
	FiniteTimeAction *playerScoreStartAnimation = CallFunc::create([playerScoreCount](){playerScoreCount->setString(string("200"));});

	Node *detail = _detailController->getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = _detailController->getDetailFallenToOneBlockAnimation(detail);
	vector<Sprite*> tetraminosInBottom = _tetraminosController->getTetraminosVerticallLineCombination();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->getVericalLineCombinationExplosion();});
	vector<Node*> detailTetraminos = _tetraminosController->getVerticalDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, playerScoreAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, playerScoreStartAnimation, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerUseRocketSpellTutorial()
{
	LabelTTF *playerScoreCount = _scoreController->getPlayerScoreCountLabel();
	FiniteTimeAction *playerScoreAnimation = _scoreController->getPlayerScoreAnimationWithCountLabelAndFinalCount(playerScoreCount, string("160"));
	FiniteTimeAction *playerScoreStartAnimation = CallFunc::create([playerScoreCount](){playerScoreCount->setString(string("200"));});

	Node *detail = _detailController->getDetailForControllsTutorial();

	FiniteTimeAction *detailAppearanceAnimation = _detailController->getDetailAppearanceAnimation(detail);
	FiniteTimeAction *useSpellKeyAnimation = _playerActionsController->getUseSpellKeyAnimation();
	FiniteTimeAction *explosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->getSpellExplosion();});

	FiniteTimeAction *detailHideAnimation = Hide::create();
	FiniteTimeAction *hideDetail = TargetedAction::create(detail, detailHideAnimation);

	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *placeDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);

	FiniteTimeAction *detailShowAnimation = Show::create();
	FiniteTimeAction *showDetail = TargetedAction::create(detail, detailShowAnimation);

	ActionInterval *sequence  = Sequence::create(detailAppearanceAnimation, useSpellKeyAnimation, explosionAnimation, playerScoreAnimation , hideDetail, placeDetailAtStartPositon, showDetail, playerScoreStartAnimation, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerFightWithBossTutorial()
{
	Node *detail = _detailController->getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = _detailController->getDetailFallenToBossLineAnimation(detail);
	 _tetraminosController->makeBossEnvironmentTetraminos();

	LabelTTF *bossLifeCount = _victoryConditionController->getBossLifeCountLabel();
	FiniteTimeAction *victoryConditionAnimation = _victoryConditionController->getVictoryConditionAnimationWithLifeLabel(bossLifeCount);
	FiniteTimeAction *bossLifeCountStartAnimation = CallFunc::create([bossLifeCount](){bossLifeCount->setString(string("1"));});

	vector<Sprite*> tetraminosInBossLine = _tetraminosController->getBossLineTetraminosCombination();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->makeBottomExplosionWithHeight(4);});
	vector<Node*> detailTetraminos = _tetraminosController->getBottomDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosInBossLine, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosInBossLine, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, victoryConditionAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, bossLifeCountStartAnimation, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerUseRandomExplosionsSpellTutorial()
{
	FiniteTimeAction *useSpellKeyAnimation = _playerActionsController->getUseSpellButtonAnimationWithKey(gameTutorialUseRandomExplosionsSpellControlKey);
	
	vector<Sprite*> tetraminosForRandomExplosions = _tetraminosController->getTetraminosForRandomExplosions();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->makeRandomSpellExplosions();});
	vector<Node*> detailTetraminos;
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosForRandomExplosions, detailTetraminos);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosForRandomExplosions, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(useSpellKeyAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerUseFirestormSpellTutorial()
{
	FiniteTimeAction *useSpellKeyAnimation = _playerActionsController->getUseSpellButtonAnimationWithKey(gameTutorialUseFirestormSpellControlKey);
	FiniteTimeAction *firestormAnimation = _explosionsController->getFirestormAnimation();
	vector<Sprite*> tetraminosForFirestorm = _tetraminosController->getTetraminosForFirestorm();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->makeFirestormSpellExplosions();});
	vector<Node*> detailTetraminos;
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosForFirestorm, detailTetraminos);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosForFirestorm, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(1.4f);

	ActionInterval *sequence  = Sequence::create(useSpellKeyAnimation, firestormAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerUseCohesionSpellTutorial()
{
	FiniteTimeAction *useSpellKeyAnimation = _playerActionsController->getUseSpellButtonAnimationWithKey(gameTutorialUseCohesionSpellControlKey);
	vector<Sprite*> tetraminosForCohesion = _tetraminosController->getTetraminosForCohesion();
	FiniteTimeAction *tetraminosExplosionAnimation = _explosionsController->getTetraminosExplosionAnimationForCallback([this](){_explosionsController->makeCohesionSpellExplosions();});
	vector<Node*> cohesionTetraminos = _tetraminosController->getCohesionTetraminos();
	FiniteTimeAction *tetraminosCohesionAnimation = _tetraminosController->getCohesionAnimationWithTetraminos(cohesionTetraminos);
	vector<Node*> detailTetraminos;
	FiniteTimeAction *tetraminosDisappearanceAnimation = _tetraminosController->getTetraminosDisappearanceAnimation(tetraminosForCohesion, cohesionTetraminos);
	FiniteTimeAction *actionWithTetraminosAppearance = _tetraminosController->getTetraminosAppearanceAnimation(tetraminosForCohesion, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(useSpellKeyAnimation, tetraminosCohesionAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}