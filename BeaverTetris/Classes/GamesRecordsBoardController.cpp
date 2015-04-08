#include "GamesRecordsBoardController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GamePlayersDatabase.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "StringsSupporter.h"

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
	int recordsCount = getRecordsCount();
	for (int recordIndex = 0; recordIndex < recordsCount; recordIndex++)
	{
		Node *recordPad = getRecordPadWithIndex(recordIndex);
		Node *playerNameLabel = getPlayerNameLabelWithIndex(recordIndex);
		Node *playerScoreLabel = getPlayerScoreLabelWithIndex(recordIndex);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(playerScoreLabel, recordPad, gameRecordsBoardPlayerScoreLabelKey);
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
	Sprite *recordPad = Sprite::create("HelloWorld.png");
	recordPad->setScaleX(0.3f);
	recordPad->setScaleY(0.15f);
	recordPad->setColor(Color3B::BLACK);
	
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(gameRecordsBoardControllerKey);
	Vec2 recordPadPosition = Vec2(0, offset.y * aIndex);
	recordPad->setPosition(recordPadPosition);
	return recordPad;
}

Node* GamesRecordsBoardController::getPlayerNameLabelWithIndex(int aIndex)
{
	LabelTTF *playerNameLabel = GameViewStyleHelper::getStandardLabel();
	playerNameLabel->setFontSize(80);
	string playerIndex = StringsSupporter::getStringFromNumber(aIndex + 1) + string(")") + string(" ");
	string playerName = _gamePlayersDatabase->getPlayerNameForIndex(aIndex);
	string playerInformation = playerIndex + playerName;
	playerNameLabel->setString(playerInformation);
	return playerNameLabel;
}

Node* GamesRecordsBoardController::getPlayerScoreLabelWithIndex(int aIndex)
{
	LabelTTF *playerScoreLabel = GameViewStyleHelper::getStandardLabel();
	playerScoreLabel->setFontSize(80);
	string playerScore = StringsSupporter::getStringFromNumber(_gamePlayersDatabase->getPlayerScoreForIndex(aIndex));
	playerScoreLabel->setString(playerScore);
	return playerScoreLabel;
}