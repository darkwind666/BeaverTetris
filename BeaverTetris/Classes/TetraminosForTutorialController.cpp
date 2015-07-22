#include "TetraminosForTutorialController.h"
#include "GameDesignConstants.h"
#include "GameElementsDataHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "KeysForEnumsDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "TutorialConstants.h"

using namespace cocos2d;
using namespace std;

TetraminosForTutorialController::TetraminosForTutorialController(void)
{
}


TetraminosForTutorialController::~TetraminosForTutorialController(void)
{
}

vector<Sprite*> TetraminosForTutorialController::getTetraminosInBottom()
{
	int bottomElements[] = {1,2,0,1,2,2,2,1,3,1};
	vector<Sprite*> elements = getElementsFromArrayWithYIndex(bottomElements, 1);
	return elements;
}

vector<Sprite*> TetraminosForTutorialController::getElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex)
{
	vector<Sprite*> tetraminoElementsLine;
	for (int xIndex = 0; xIndex < tetrisBlocksWidth; xIndex++)
	{
		int tetraminoTag = aSourceMassive[xIndex];
		Sprite *tetraminoView = getTetraminoViewForType(tetraminoTag);
		tetraminoView->setTag(tetraminoTag);
		Vec2 tetraminoPosition = getTetraminoPositionForIndexXY(xIndex, yIndex);
		tetraminoView->setPosition(tetraminoPosition);
		this->addChild(tetraminoView);
		tetraminoElementsLine.push_back(tetraminoView);
	}
	return tetraminoElementsLine;
}

Sprite* TetraminosForTutorialController::getTetraminoViewForType(int aType)
{
	Sprite *tetraminoView;
	if (aType > 0)
	{
		TetraminoType type = (TetraminoType)aType;
		KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
		string typeName = keysForEnumsDataSource->getKeyForTetraminoType(type);
		string teraminoImageName = GameFileExtensionMaker::getGraphicWithExtension(typeName);
		tetraminoView = Sprite::createWithSpriteFrameName(teraminoImageName);
	}
	else
	{
		tetraminoView = Sprite::create();
	}
	return tetraminoView;
}

Vec2 TetraminosForTutorialController::getTetraminoPositionForIndexXY(int xIndex, int yIndex)
{
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 position = Vec2(offset.x * xIndex, offset.y * yIndex);
	return position;
}

vector<Node*> TetraminosForTutorialController::getBottomDetailTetraminos(Node* aDetail)
{
	vector<Node*> detailTetraminos;
	Node* bottomTetramino = aDetail->getChildByTag(tetramino3Tag);
	detailTetraminos.push_back(bottomTetramino);
	return detailTetraminos;
}

vector<Node*> TetraminosForTutorialController::getVerticalDetailTetraminos(Node *aDetail)
{
	vector<Node*> detailTetraminos;
	Node* verticalTetramino1 = aDetail->getChildByTag(tetramino3Tag);
	detailTetraminos.push_back(verticalTetramino1);
	Node* verticalTetramino2 = aDetail->getChildByTag(tetramino2Tag);
	detailTetraminos.push_back(verticalTetramino2);
	Node* verticalTetramino3 = aDetail->getChildByTag(tetramino1Tag);
	detailTetraminos.push_back(verticalTetramino3);
	return detailTetraminos;
}

void TetraminosForTutorialController::makeBossEnvironmentTetraminos()
{
	int tetraminoElementsInBoard[standartDetailHeight][tetrisBlocksWidth] = {
		{0,0,2,2,1,1,1,3,3,3},
		{1,1,2,2,3,0,4,4,1,1},
		{0,1,1,3,3,3,4,4,1,1},
	};

	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		makeElementsFromArrayWithYIndex(&tetraminoElementsInBoard[0][0], yIndex);
	}
}

vector<Sprite*> TetraminosForTutorialController::getBossLineTetraminosCombination()
{
	int elementsInBossLine[] = {6,1,0,3,4,1,1,5,3,3};
	vector<Sprite*> elements = getElementsFromArrayWithYIndex(elementsInBossLine, 4);
	vector<Sprite*> tetraminoInBottom = elements;
	return tetraminoInBottom;
}

void TetraminosForTutorialController::makeElementsFromArrayWithYIndex(int *aSourceMassive, int yIndex)
{
	int elements[] = {0,0,0,0,0,0,0,0,0,0};
	for (int xIndex = 0; xIndex < tetrisBlocksWidth; xIndex++)
	{
		int tetraminoTag = aSourceMassive[yIndex * tetrisBlocksWidth + xIndex];
		elements[xIndex] = tetraminoTag;
	}
	getElementsFromArrayWithYIndex(elements, yIndex + 1);
}

vector<Sprite*> TetraminosForTutorialController::getTetraminosHorizontalLineCombination()
{
	int bottomElements[] = {0,0,0,1,1,1,0,0,0,0};
	vector<Sprite*> elements = getElementsFromArrayWithYIndex(bottomElements, 1);
	return elements;
}

vector<Sprite*> TetraminosForTutorialController::getTetraminosVerticallLineCombination()
{
	int bottomElements[] = {0,0,1,1,1,0,0,0,0,0};
	vector<Sprite*> elements = getElementsFromArrayWithYIndex(bottomElements, 1);
	vector<Sprite*> tetraminoInBottom;
	tetraminoInBottom.push_back(elements[2]);
	return tetraminoInBottom;
}

vector<Sprite*> TetraminosForTutorialController::getTetraminosForRandomExplosions()
{

	vector<Sprite*> elementsForExplosions;

	int upLine[] = {0,0,2,2,1,1,1,3,3,3};

	vector<Sprite*> upLineElements = getElementsFromArrayWithYIndex(upLine, 3);
	elementsForExplosions.push_back(upLineElements[6]);
	elementsForExplosions.push_back(upLineElements[5]);
	elementsForExplosions.push_back(upLineElements[8]);

	int middleLine[] = {1,1,2,2,3,0,4,4,1,1};

	vector<Sprite*> middleLineElements = getElementsFromArrayWithYIndex(middleLine, 2);
	elementsForExplosions.push_back(middleLineElements[2]);
	elementsForExplosions.push_back(middleLineElements[3]);

	int downLine[] = {0,1,1,3,3,3,4,4,1,1};

	vector<Sprite*> downLineElements = getElementsFromArrayWithYIndex(downLine, 1);
	elementsForExplosions.push_back(downLineElements[1]);
	elementsForExplosions.push_back(downLineElements[3]);
	elementsForExplosions.push_back(downLineElements[2]);

	return elementsForExplosions;
}

vector<Sprite*>  TetraminosForTutorialController::getTetraminosForFirestorm()
{
	vector<Sprite*> elementsForExplosions;

	int middleLine[] = {1,1,2,2,3,0,4,4,1,1};

	vector<Sprite*> middleLineElements = getElementsFromArrayWithYIndex(middleLine, 2);
	elementsForExplosions.push_back(middleLineElements[1]);
	elementsForExplosions.push_back(middleLineElements[2]);
	elementsForExplosions.push_back(middleLineElements[3]);
	elementsForExplosions.push_back(middleLineElements[4]);
	elementsForExplosions.push_back(middleLineElements[6]);
	elementsForExplosions.push_back(middleLineElements[7]);
	elementsForExplosions.push_back(middleLineElements[8]);
	elementsForExplosions.push_back(middleLineElements[9]);

	getTetraminosInBottom();

	return elementsForExplosions;
}

vector<Sprite*> TetraminosForTutorialController::getTetraminosForCohesion()
{
	vector<Sprite*> elementsForExplosions;

	int middleLine[] = {1,0,2,2,3,0,4,4,1,1};

	vector<Sprite*> middleLineElements = getElementsFromArrayWithYIndex(middleLine, 2);
	elementsForExplosions.insert(elementsForExplosions.end(), middleLineElements.begin(), middleLineElements.end());

	int downLine[] = {0,1,1,0,3,3,0,4,1,1};

	vector<Sprite*> downLineElements = getElementsFromArrayWithYIndex(downLine, 1);
	elementsForExplosions.insert(elementsForExplosions.end(), downLineElements.begin(), downLineElements.end());

	return elementsForExplosions;
}

vector<Node*> TetraminosForTutorialController::getCohesionTetraminos()
{
	vector<Node*> elementsForExplosions;

	int downLine[] = {1,0,0,1,0,0,1,0,0,0};

	vector<Sprite*> downLineElements = getElementsFromArrayWithYIndex(downLine, 1);
	elementsForExplosions.insert(elementsForExplosions.end(), downLineElements.begin(), downLineElements.end());

	int middleLine[] = {0,1,0,0,0,1,0,0,0,0};

	vector<Sprite*> middleLineElements = getElementsFromArrayWithYIndex(middleLine, 2);
	elementsForExplosions.insert(elementsForExplosions.end(), middleLineElements.begin(), middleLineElements.end());

	return elementsForExplosions;
}

FiniteTimeAction* TetraminosForTutorialController::getTetraminosDisappearanceAnimation(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos)
{
	function<FiniteTimeAction*()> action = [](){return Hide::create();};
	FiniteTimeAction *animationHideTetraminos = getAnimationWithTetraminosAndDetailAndAction(aTetraminos, aDetailTetraminos, action);
	return animationHideTetraminos;
}


FiniteTimeAction* TetraminosForTutorialController::getTetraminosAppearanceAnimation(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos)
{
	function<FiniteTimeAction*()> action = [](){return Show::create();};
	FiniteTimeAction *animationShowTetraminos = getAnimationWithTetraminosAndDetailAndAction(aTetraminos, aDetailTetraminos, action);
	return animationShowTetraminos;
}

FiniteTimeAction* TetraminosForTutorialController::getAnimationWithTetraminosAndDetailAndAction(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos, function<FiniteTimeAction*()> action)
{
	FiniteTimeAction *tetraminosSequence = getTetraminosSequenceWithAction(aTetraminos, action);
	FiniteTimeAction *animation = getAnimationInDetailWithTetraminosSequenceAndAction(aDetailTetraminos, tetraminosSequence, action);
	FiniteTimeAction *animationWithTetraminos = TargetedAction::create(this, animation);
	return animationWithTetraminos;
}

FiniteTimeAction* TetraminosForTutorialController::getTetraminosSequenceWithAction(vector<Sprite*> aTetraminos, function<FiniteTimeAction*()> action)
{
	Vector<FiniteTimeAction*> actions;
	vector<Sprite*>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		Sprite *tetraminoView = *tetraminosIterator;
		FiniteTimeAction *animationWithTetramino = TargetedAction::create(tetraminoView, action());
		actions.pushBack(animationWithTetramino);
	}
	FiniteTimeAction *tetraminosSequence = Sequence::create(actions);
	return tetraminosSequence;
}

FiniteTimeAction* TetraminosForTutorialController::getAnimationInDetailWithTetraminosSequenceAndAction(vector<Node*> aDetailTetraminos, FiniteTimeAction* aTetraminosSequence, function<FiniteTimeAction*()> action)
{
	FiniteTimeAction *animation;
	if (aDetailTetraminos.size() > 0)
	{
		FiniteTimeAction *animationWithTetraminosInDetail = getAnimationWithTetraminosInDetail(aDetailTetraminos, action);
		animation = Sequence::create(aTetraminosSequence, animationWithTetraminosInDetail, nullptr);
	}
	else
	{
		animation = aTetraminosSequence;
	}
	return animation;
}

FiniteTimeAction* TetraminosForTutorialController::getAnimationWithTetraminosInDetail(vector<Node*> aDetailTetraminos, function<FiniteTimeAction*()> action)
{
	Vector<FiniteTimeAction*> actions;
	vector<Node*>::iterator tetraminosIterator;
	for (tetraminosIterator = aDetailTetraminos.begin(); tetraminosIterator != aDetailTetraminos.end(); tetraminosIterator++)
	{
		Node *tetraminoView = *tetraminosIterator;
		FiniteTimeAction *animationWithTetramino = TargetedAction::create(tetraminoView, action());
		actions.pushBack(animationWithTetramino);
	}
	FiniteTimeAction *tetraminosInDetailSequence = Sequence::create(actions);
	FiniteTimeAction *animationWithTetraminos = TargetedAction::create(this, tetraminosInDetailSequence);
	return animationWithTetraminos;
}

FiniteTimeAction* TetraminosForTutorialController::getCohesionAnimationWithTetraminos(vector<Node*> aTetraminos)
{
	Vector<FiniteTimeAction*> actions;
	vector<Node*>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		Node *tetraminoView = *tetraminosIterator;
		addCohessionAnimation(tetraminoView, &actions);
	}
	FiniteTimeAction *tetraminosSequence = Sequence::create(actions);
	FiniteTimeAction *animationWithTetraminos = TargetedAction::create(this, tetraminosSequence);
	return animationWithTetraminos;
}

void TetraminosForTutorialController::addCohessionAnimation(cocos2d::Node *aView, cocos2d::Vector<cocos2d::FiniteTimeAction*> *actions)
{
	if (aView->getTag() > 0)
	{
		aView->setOpacity(0.0f);
		FiniteTimeAction *showNode = Show::create();
		FiniteTimeAction *setOpacity = CallFuncN::create([](Node *aTarget){aTarget->setOpacity(0.0f);});
		FiniteTimeAction *showTetramino = FadeIn::create(0.3f);
		FiniteTimeAction *sequence = Sequence::create(setOpacity, showNode, showTetramino, nullptr);
		FiniteTimeAction *animationWithTetramino = TargetedAction::create(aView, sequence);
		actions->pushBack(animationWithTetramino);
	}
}
