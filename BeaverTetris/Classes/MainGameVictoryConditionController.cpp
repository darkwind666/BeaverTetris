#include "MainGameVictoryConditionController.h"
#include "VictoryConditionViewDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"

using namespace std;
using namespace cocos2d;

MainGameVictoryConditionController::MainGameVictoryConditionController(void)
{
	_victoryConditionViewDataSource = new VictoryConditionViewDataSource();
	_viewElements = vector<VictoryConditionViewElements>();
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, victoryConditionPadImageKey);
}


MainGameVictoryConditionController::~MainGameVictoryConditionController(void)
{
	delete _victoryConditionViewDataSource;
}

void MainGameVictoryConditionController::update(float delta)
{
	int victoryConditionsCount = _victoryConditionViewDataSource->getVictoryConditionsCount();
	if (victoryConditionsCount != _viewElements.size())
	{
		vector<VictoryConditionViewElements> viewElements = makeViewElements();
		addViewElements(viewElements);
	}
	updateViews();
}

vector<VictoryConditionViewElements> MainGameVictoryConditionController::makeViewElements()
{
	vector<VictoryConditionViewElements> victoryConditionsViews;
	int victoryConditionsCount = _victoryConditionViewDataSource->getVictoryConditionsCount();
	for (int conditionIndex = 0; conditionIndex < victoryConditionsCount; conditionIndex++)
	{
		VictoryConditionViewElements victoryConditionView;
		victoryConditionView.image = getVictoryConditionImageViewForIndex(conditionIndex);
		victoryConditionView.label = getVictoryConditionStatusViewForIndex(conditionIndex);
		setElementsPositionsWithIndex(victoryConditionView, conditionIndex);
		victoryConditionsViews.push_back(victoryConditionView);
	}
	return victoryConditionsViews;
}

Sprite* MainGameVictoryConditionController::getVictoryConditionImageViewForIndex(int aConditionIndex)
{
	string victoryConditionImageName = _victoryConditionViewDataSource->getVictoryConditionIconImageForIndex(aConditionIndex);
	Sprite *victoryConditionView = Sprite::createWithSpriteFrameName(victoryConditionImageName);
	Vec2 victoryConditionViewPosition = _victoryConditionViewDataSource->getVictoryConditionIconImagePositionForIndex(aConditionIndex);
	victoryConditionView->setPosition(victoryConditionViewPosition);
	return victoryConditionView;
}

LabelTTF* MainGameVictoryConditionController::getVictoryConditionStatusViewForIndex(int aConditionIndex)
{
	LabelTTF *victoryConditionStatus = GameViewStyleHelper::getStandardLabel();
	victoryConditionStatus->setFontSize(12.0f);
	victoryConditionStatus->setTag(aConditionIndex);
	Vec2 victoryConditionStatusPosition = _victoryConditionViewDataSource->getVictoryConditionInformationPositionForIndex(aConditionIndex);
	victoryConditionStatus->setPosition(victoryConditionStatusPosition);
	return victoryConditionStatus;
}

void MainGameVictoryConditionController::setElementsPositionsWithIndex(VictoryConditionViewElements &victoryConditionView, int aIndex)
{
	int victoryConditionsCount = _victoryConditionViewDataSource->getVictoryConditionsCount();
	if (victoryConditionsCount > 2 && aIndex == 1)
	{
		Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(victoryConditionHudControllerKey);
		Vec2 imagePosition = victoryConditionView.image->getPosition();
		victoryConditionView.image->setPosition(imagePosition + offset);
		Vec2 labelPosition = victoryConditionView.label->getPosition();
		victoryConditionView.label->setPosition(labelPosition + offset);
	}
}

void MainGameVictoryConditionController::addViewElements(std::vector<VictoryConditionViewElements> aViewElements)
{
	cleanViews();
	vector<VictoryConditionViewElements>::iterator viewsIterator;
	for (viewsIterator = aViewElements.begin(); viewsIterator != aViewElements.end(); viewsIterator++)
	{
		VictoryConditionViewElements viewsElement = *viewsIterator;
		this->addChild(viewsElement.image);
		this->addChild(viewsElement.label);
		_viewElements.push_back(viewsElement);
	}
}

void MainGameVictoryConditionController::cleanViews()
{
	vector<VictoryConditionViewElements>::iterator viewsIterator;
	for (viewsIterator = _viewElements.begin(); viewsIterator != _viewElements.end(); viewsIterator++)
	{
		VictoryConditionViewElements viewsElement = *viewsIterator;
		this->removeChild(viewsElement.image);
		this->removeChild(viewsElement.label);
	}
	_viewElements.clear();
}

void MainGameVictoryConditionController::updateViews()
{
	vector<VictoryConditionViewElements>::iterator viewsIterator;
	for (viewsIterator = _viewElements.begin(); viewsIterator != _viewElements.end(); viewsIterator++)
	{
		VictoryConditionViewElements viewsElement = *viewsIterator;
		int labelTag = viewsElement.label->getTag();
		string viewStatus = _victoryConditionViewDataSource->getVictoryConditionInformationForIndex(labelTag);
		viewsElement.label->setString(viewStatus);
	}
}