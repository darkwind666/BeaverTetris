#include "TetraminisDetailsFactory.h"
#include "GameDesignConstants.h"

using namespace std;

TetraminisDetailsFactory::TetraminisDetailsFactory()
{
	
}

TetraminisDetailsFactory::~TetraminisDetailsFactory(void)
{
}

map<TetraminoDetailType, TetraminoDetailInformation> TetraminisDetailsFactory::getDetailsTypesData()
{
	map<TetraminoDetailType, TetraminoDetailInformation> detailsData = map<TetraminoDetailType, TetraminoDetailInformation>();

	TetraminoDetailInformation detail1;
	detail1.rotateble = true;
	int tetraminoElements1[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,0},
		{0,1,1},
	};
	
	TetraminoDetailInformation detail2;
	detail2.rotateble = true;
	int tetraminoElements2[standartDetailWidth][standartDetailHeight] = {
		{1,0,1},
		{1,1,1},
		{0,0,0},
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

	TetraminoDetailInformation detail5;
	detail5.rotateble = true;
	int tetraminoElements5[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{1,1,1},
		{0,0,0},
	};

	copyMasiveToVectorInStructure(&tetraminoElements1[0][0], detail1);
	copyMasiveToVectorInStructure(&tetraminoElements2[0][0], detail2);
	copyMasiveToVectorInStructure(&tetraminoElements3[0][0], detail3);
	copyMasiveToVectorInStructure(&tetraminoElements4[0][0], detail4);
	copyMasiveToVectorInStructure(&tetraminoElements5[0][0], detail5);

	detailsData[kTetraminoDetail1] = detail1;
	detailsData[kTetraminoDetail2] = detail2;
	detailsData[kTetraminoDetail3] = detail3;
	detailsData[kTetraminoDetail4] = detail4;
	detailsData[kTetraminoDetail5] = detail5;

	return detailsData;
}

void TetraminisDetailsFactory::copyMasiveToVectorInStructure(int *aSourceMassive, TetraminoDetailInformation &aInformation)
{
	vector< vector<int> > tetraminoElements;
	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		vector<int> tetraminoElementsLine = getTetraminosElementsLineFromSource(yIndex, aSourceMassive);
		tetraminoElements.push_back(tetraminoElementsLine);
	}
	aInformation.tetraminoElements = tetraminoElements;
}

vector<int> TetraminisDetailsFactory::getTetraminosElementsLineFromSource(int yIndex, int *aSourceMassive)
{
	vector<int> tetraminoElementsLine;
	for (int xIndex = 0; xIndex < standartDetailWidth; xIndex++)
	{
		int tetraminoTag = aSourceMassive[yIndex * standartDetailHeight + xIndex];
		tetraminoElementsLine.push_back(tetraminoTag);
	}
	return tetraminoElementsLine;
}