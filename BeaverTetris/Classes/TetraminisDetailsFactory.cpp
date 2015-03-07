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

	detailsData[kTetraminoDetail1] = getDetailType1Information();
	detailsData[kTetraminoDetail2] = getDetailType2Information();
	detailsData[kTetraminoDetail3] = getDetailType3Information();
	detailsData[kTetraminoDetail4] = getDetailType4Information();
	detailsData[kTetraminoDetail5] = getDetailType5Information();
	detailsData[kTetraminoDetail6] = getDetailType6Information();
	detailsData[kTetraminoDetail7] = getDetailType7Information();
	detailsData[kTetraminoDetail8] = getDetailType8Information();

	return detailsData;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType1Information()
{
	TetraminoDetailInformation detail1;
	detail1.detailForms = vector <  vector< vector<int> >  >();
	detail1.rotateble = true;

	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,0},
		{0,1,1},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail1);

	int form2[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{1,1,0},
		{1,0,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail1);

	return detail1;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType2Information()
{
	TetraminoDetailInformation detail2;
	detail2.detailForms = vector <  vector< vector<int> >  >();
	detail2.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{1,0,1},
		{1,1,1},
		{0,0,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail2);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{0,1,1},
		{0,1,0},
		{0,1,1},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail2);

	int form3[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{1,0,1},
	};
	copyMasiveToVectorInStructure(&form3[0][0], detail2);

	int form4[standartDetailWidth][standartDetailHeight] = {
		{1,1,0},
		{0,1,0},
		{1,1,0},
	};
	copyMasiveToVectorInStructure(&form4[0][0], detail2);
	
	return detail2;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType3Information()
{
	TetraminoDetailInformation detail3;
	detail3.detailForms = vector <  vector< vector<int> >  >();
	detail3.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{0,0,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail3);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{0,1,0},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail3);
	
	return detail3;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType4Information()
{
	TetraminoDetailInformation detail4;
	detail4.detailForms = vector <  vector< vector<int> >  >();
	detail4.rotateble = false;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,0},
		{1,1,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail4);
	
	return detail4;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType5Information()
{
	TetraminoDetailInformation detail5;
	detail5.detailForms = vector <  vector< vector<int> >  >();
	detail5.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{1,1,1},
		{0,0,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail5);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{0,1,1},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail5);
	
	int form3[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form3[0][0], detail5);
	
	int form4[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{1,1,0},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form4[0][0], detail5);
	
	return detail5;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType6Information()
{
	TetraminoDetailInformation detail6;
	detail6.detailForms = vector <  vector< vector<int> >  >();
	detail6.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{0,1,1},
		{1,1,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail6);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{1,0,0},
		{1,1,0},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail6);
	
	return detail6;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType7Information()
{
	TetraminoDetailInformation detail7;
	detail7.detailForms = vector <  vector< vector<int> >  >();
	detail7.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{0,1,0},
		{0,1,1},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail7);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{1,0,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail7);
	
	int form3[standartDetailWidth][standartDetailHeight] = {
		{1,1,0},
		{0,1,0},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form3[0][0], detail7);
	
	int form4[standartDetailWidth][standartDetailHeight] = {
		{0,0,1},
		{1,1,1},
		{0,0,0},
	};
	copyMasiveToVectorInStructure(&form4[0][0], detail7);
	
	return detail7;
}

TetraminoDetailInformation TetraminisDetailsFactory::getDetailType8Information()
{
	TetraminoDetailInformation detail8;
	detail8.detailForms = vector <  vector< vector<int> >  >();
	detail8.rotateble = true;
	
	int form1[standartDetailWidth][standartDetailHeight] = {
		{0,1,0},
		{0,1,0},
		{1,1,0},
	};
	copyMasiveToVectorInStructure(&form1[0][0], detail8);
	
	int form2[standartDetailWidth][standartDetailHeight] = {
		{1,0,0},
		{1,1,1},
		{0,0,0},
	};
	copyMasiveToVectorInStructure(&form2[0][0], detail8);
	
	int form3[standartDetailWidth][standartDetailHeight] = {
		{0,1,1},
		{0,1,0},
		{0,1,0},
	};
	copyMasiveToVectorInStructure(&form3[0][0], detail8);
	
	int form4[standartDetailWidth][standartDetailHeight] = {
		{0,0,0},
		{1,1,1},
		{0,0,1},
	};
	copyMasiveToVectorInStructure(&form4[0][0], detail8);
	
	return detail8;
}


void TetraminisDetailsFactory::copyMasiveToVectorInStructure(int *aSourceMassive, TetraminoDetailInformation &aInformation)
{
	vector< vector<int> > tetraminoElements;
	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		vector<int> tetraminoElementsLine = getTetraminosElementsLineFromSource(yIndex, aSourceMassive);
		tetraminoElements.push_back(tetraminoElementsLine);
	}
	aInformation.detailForms.push_back(tetraminoElements);
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