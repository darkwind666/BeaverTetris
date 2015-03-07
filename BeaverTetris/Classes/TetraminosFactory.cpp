#include "TetraminosFactory.h"
#include "Tetramino.h"

using namespace std;

TetraminosFactory::TetraminosFactory(void)
{
	_tetraminosData = getTetraminosData();
}

TetraminosFactory::~TetraminosFactory(void)
{
}

map<TetraminoType, TetraminoInformation> TetraminosFactory::getTetraminosData()
{
	map<TetraminoType, TetraminoInformation> tetraminosData;

	TetraminoInformation tetraminoEmptyData;
	tetraminoEmptyData.tetraminoLivesCount = 0;
	tetraminoEmptyData.tetraminoCost = 0;
	tetraminosData[kTetraminoEmpty] = tetraminoEmptyData;

	TetraminoInformation tetraminoGreenData;
	tetraminoGreenData.tetraminoLivesCount = 1;
	tetraminoGreenData.tetraminoCost = 10;
	tetraminosData[kTetraminoGreen] = tetraminoGreenData;

	TetraminoInformation tetraminoBlueData;
	tetraminoBlueData.tetraminoLivesCount = 1;
	tetraminoBlueData.tetraminoCost = 20;
	tetraminosData[kTetraminoBlue] = tetraminoBlueData;

	TetraminoInformation tetraminoGoldData;
	tetraminoGoldData.tetraminoLivesCount = 1;
	tetraminoGoldData.tetraminoCost = 40;
	tetraminosData[kTetraminoGold] = tetraminoGoldData;

	TetraminoInformation tetraminoBlackData;
	tetraminoBlackData.tetraminoLivesCount = 3;
	tetraminoBlackData.tetraminoCost = 30;
	tetraminosData[kTetraminoBlack] = tetraminoBlackData;

	TetraminoInformation tetraminoBossQueenData;
	tetraminoBossQueenData.tetraminoLivesCount = 10;
	tetraminoBossQueenData.tetraminoCost = 70;
	tetraminosData[kTetraminoBossQueen] = tetraminoBossQueenData;

	TetraminoInformation tetraminoBossPrincessData;
	tetraminoBossPrincessData.tetraminoLivesCount = 14;
	tetraminoBossPrincessData.tetraminoCost = 60;
	tetraminosData[kTetraminoBossPrincess] = tetraminoBossPrincessData;

	TetraminoInformation tetraminoBossKingData;
	tetraminoBossKingData.tetraminoLivesCount = 20;
	tetraminoBossKingData.tetraminoCost = 100;
	tetraminosData[kTetraminoBossKing] = tetraminoBossKingData;

	return tetraminosData;
}

Tetramino* TetraminosFactory::getNewTetraminoWithType(TetraminoType aType)
{
	TetraminoInformation tetraminoData = _tetraminosData[aType];
	Tetramino *newTetramino = new Tetramino(aType, tetraminoData.tetraminoLivesCount, tetraminoData.tetraminoCost);
	return newTetramino;
}
