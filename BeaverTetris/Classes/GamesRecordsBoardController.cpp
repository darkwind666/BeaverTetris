#include "GamesRecordsBoardController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GamePlayersDatabase.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "StringsSupporter.h"
#include "GameFileExtensionMaker.h"

const int maxRecordsCount = 5;

using namespace cocos2d;

GamesRecordsBoardController::GamesRecordsBoardController(void)
{
	_gamePlayersDatabase = (GamePlayersDatabase*)ServiceLocator::getServiceForKey(gamePlayersDatabaseKey);
	makeBoardView();
}


GamesRecordsBoardController::~GamesRecordsBoardController(void)
{
}

void GamesRecordsBoardController::makeBoardView()
{
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, gameRecordsBoardPadKey);
	createRecordsBoard();
	GameViewStyleHelper::addBackButtonToParentNodeWithKey(this, gameRecordsGoToMainMenuButtonKey);
}

void GamesRecordsBoardController::createRecordsBoard()
{
	int recordsCount = getRecordsCount();
	for (int recordIndex = 0; recordIndex < recordsCount; recordIndex++)
	{
		Node *recordPad = getRecordPadWithIndex(recordIndex);
		Node *playerNameLabel = getPlayerNameLabelWithIndex(recordIndex);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(playerNameLabel, recordPad, gameRecordsBoardPlayerNameLabelKey);
		this->addChild(recordPad);
	}
}

int GamesRecordsBoardController::getRecordsCount()
{
	int recordsCount = _gamePlayersDatabase->getPlayersCount();
	if (recordsCount > maxRecordsCount)
	{
		recordsCount = maxRecordsCount;
	}
	return recordsCount;
}

Node* GamesRecordsBoardController::getRecordPadWithIndex(int aIndex)
{
	string recordPadImageName = getRecordPadImageNameWithIndex(aIndex);
	Sprite *recordPad = Sprite::createWithSpriteFrameName(recordPadImageName);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(gameRecordsBoardControllerKey);
	Vec2 recordPadPosition = Vec2(0, offset.y * aIndex);
	recordPad->setPosition(recordPadPosition);
	return recordPad;
}

string GamesRecordsBoardController::getRecordPadImageNameWithIndex(int aIndex)
{
	string recordPadImageName = gameRecordsBoardLeaderPlacePadKey;
	if (aIndex > 2)
	{
		recordPadImageName = gameRecordsBoardPlacePadKey;
	}
	string recordPadImageNameWithFileExtension = GameFileExtensionMaker::getGraphicWithExtension(recordPadImageName);
	return recordPadImageNameWithFileExtension;
}

Node* GamesRecordsBoardController::getPlayerNameLabelWithIndex(int aIndex)
{
	LabelTTF *playerNameLabel = GameViewStyleHelper::getStandardLabel();
	playerNameLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	float fontSize = getLabelFontSizeWithIndex(aIndex);
	playerNameLabel->setFontSize(fontSize);
	string playerIndex = StringsSupporter::getStringFromNumber(aIndex + 1) + string(")") + string(" ");
	string playerName = _gamePlayersDatabase->getPlayerNameForIndex(aIndex);
	string playerScore = StringsSupporter::getStringFromNumber(_gamePlayersDatabase->getPlayerScoreForIndex(aIndex));
	string playerInformation = playerIndex + playerName + string(" ") + playerScore;
	playerNameLabel->setString(playerInformation);
	return playerNameLabel;
}

float GamesRecordsBoardController::getLabelFontSizeWithIndex(int aIndex)
{
	float fontSize = 19;
	if (aIndex > 2)
	{
		fontSize = 17;
	}
	return fontSize;
}