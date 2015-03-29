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

	TetraminoInformation tetraminoRedData;
	tetraminoRedData.tetraminoLivesCount = 1;
	tetraminoRedData.tetraminoCost = 1;
	tetraminosData[kTetraminoRed] = tetraminoRedData;

	TetraminoInformation tetraminoGreenData;
	tetraminoGreenData.tetraminoLivesCount = 1;
	tetraminoGreenData.tetraminoCost = 1;
	tetraminosData[kTetraminoGreen] = tetraminoGreenData;

	TetraminoInformation tetraminoBlueData;
	tetraminoBlueData.tetraminoLivesCount = 1;
	tetraminoBlueData.tetraminoCost = 1;
	tetraminosData[kTetraminoBlue] = tetraminoBlueData;

	TetraminoInformation tetraminoGoldData;
	tetraminoGoldData.tetraminoLivesCount = 2;
	tetraminoGoldData.tetraminoCost = 5;
	tetraminosData[kTetraminoGold] = tetraminoGoldData;

	TetraminoInformation tetraminoBlackData;
	tetraminoBlackData.tetraminoLivesCount = 3;
	tetraminoBlackData.tetraminoCost = 3;
	tetraminosData[kTetraminoBlack] = tetraminoBlackData;

	TetraminoInformation tetraminoBossQueenData;
	tetraminoBossQueenData.tetraminoLivesCount = 15;
	tetraminoBossQueenData.tetraminoCost = 170;
	tetraminosData[kTetraminoBossQueen] = tetraminoBossQueenData;

	TetraminoInformation tetraminoBossPrincessData;
	tetraminoBossPrincessData.tetraminoLivesCount = 15;
	tetraminoBossPrincessData.tetraminoCost = 490;
	tetraminosData[kTetraminoBossPrincess] = tetraminoBossPrincessData;

	TetraminoInformation tetraminoBossKingData;
	tetraminoBossKingData.tetraminoLivesCount = 25;
	tetraminoBossKingData.tetraminoCost = 400;
	tetraminosData[kTetraminoBossKing] = tetraminoBossKingData;

	return tetraminosData;
}

Tetramino* TetraminosFactory::getNewTetraminoWithType(TetraminoType aType)
{
	TetraminoInformation tetraminoData = _tetraminosData[aType];
	Tetramino *newTetramino = new Tetramino(aType, tetraminoData.tetraminoLivesCount, tetraminoData.tetraminoCost);
	return newTetramino;
}
