#include "TetraminisDetailsFactory.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"

using namespace std;

struct TetraminoDetailInformation
{
	bool rotateble;
	int tetraminoElements[standartDetailWidth][standartDetailHeight];
};

TetraminisDetailsFactory::TetraminisDetailsFactory(CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelDataSource = aCurrentLevelDataSource;
	_detailsTypesData = makeDetailsData();
	_createdDetailsCount = 0;
}


TetraminisDetailsFactory::~TetraminisDetailsFactory(void)
{
}

TetraminoDetail* TetraminisDetailsFactory::getNewDetail()
{
	TetraminoType tetraminoType = getRandomTetraminoType();
	TetraminoDetailType detailType = getRandomTetraminoDetailType();
	TetraminoDetail *newDetail = getNewDetailWithDetailTypeAndTetraminoType(detailType, tetraminoType);
	_createdDetailsCount++;
	return newDetail;
}

int TetraminisDetailsFactory::getCreatedDetailsCount()
{
	return _createdDetailsCount;
}

TetraminoType TetraminisDetailsFactory::getRandomTetraminoType()
{
	GameLevelInformation currentLevel = _currentLevelDataSource->getCurrentLevelData();
	vector<TetraminoType> availableTetraminos = currentLevel.availableTetraminos;
	int randomTetraminoType = GameHelper::getRandomNumberFromUpInterval(availableTetraminos.size());

	TetraminoType tetraminoType = availableTetraminos[randomTetraminoType];
	return tetraminoType;
}

TetraminoDetailType TetraminisDetailsFactory::getRandomTetraminoDetailType()
{
	GameLevelInformation currentLevel = _currentLevelDataSource->getCurrentLevelData();
	vector<TetraminoDetailType> availableTetraminoDetailsType = currentLevel.availableTetraminoDetails;
	int randomDetailType = GameHelper::getRandomNumberFromUpInterval(availableTetraminoDetailsType.size());
	TetraminoDetailType detailType = availableTetraminoDetailsType[randomDetailType];
	return detailType;
}

TetraminoDetail* TetraminisDetailsFactory::getNewDetailWithDetailTypeAndTetraminoType(TetraminoDetailType aTetraminoDetailType, TetraminoType aTetraminoType)
{
	TetraminoDetail *newDetail = new TetraminoDetail(standartDetailWidth,standartDetailHeight);
	TetraminoDetailInformation newDetailInformation = _detailsTypesData[aTetraminoDetailType];
	newDetail->setDetailRotatebleFlag(newDetailInformation.rotateble);

	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		for (int xIndex = 0; xIndex < standartDetailWidth; xIndex++)
		{
			int tetraminoFlag = newDetailInformation.tetraminoElements[yIndex][xIndex];
			Tetramino *tertraminoInDetail;
			if (tetraminoFlag > 0)
			{
				tertraminoInDetail = new Tetramino(aTetraminoType);
			}
			else
			{
				tertraminoInDetail = new Tetramino();
			}
			
			newDetail->setTetraminoForXY(tertraminoInDetail, xIndex, yIndex);
			
		}
	}

	return newDetail;
}


map<TetraminoDetailType, TetraminoDetailInformation> TetraminisDetailsFactory::makeDetailsData()
{
	map<TetraminoDetailType, TetraminoDetailInformation> detailsData = map<TetraminoDetailType, TetraminoDetailInformation>();

	TetraminoDetailInformation detail1;
	detail1.rotateble = true;
	int tetraminoElements1[standartDetailWidth][standartDetailHeight] = {
		{1,1,0},
		{0,1,0},
		{0,1,1},
	};
	
	TetraminoDetailInformation detail2;
	detail2.rotateble = true;
	int tetraminoElements2[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,0,1},
		{1,1,1},
	};
	
	TetraminoDetailInformation detail3;
	detail3.rotateble = true;
	int tetraminoElements3[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{0,0,0},
	};

	TetraminoDetailInformation detail4;
	detail4.rotateble = false;
	int tetraminoElements4[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,0},
		{1,1,0},
	};

	copyMasiveToMassive(&tetraminoElements1[0][0], &detail1.tetraminoElements[0][0]);
	copyMasiveToMassive(&tetraminoElements2[0][0], &detail2.tetraminoElements[0][0]);
	copyMasiveToMassive(&tetraminoElements3[0][0], &detail3.tetraminoElements[0][0]);
	copyMasiveToMassive(&tetraminoElements4[0][0], &detail4.tetraminoElements[0][0]);

	detailsData[kTetraminoDetail1] = detail1;
	detailsData[kTetraminoDetail2] = detail2;
	detailsData[kTetraminoDetail3] = detail3;

	return detailsData;
}

void TetraminisDetailsFactory::copyMasiveToMassive(int *aSourceMassive, int *aDestinationMassive)
{
	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		for (int xIndex = 0; xIndex < standartDetailWidth; xIndex++)
		{
			aSourceMassive[yIndex * standartDetailHeight + xIndex] = aDestinationMassive[yIndex * standartDetailHeight + xIndex];
		}
	}
}