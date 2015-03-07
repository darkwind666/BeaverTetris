#pragma once

#include <map>
#include <vector>
#include "GameEnums.h"
#include "GameStructures.h"

class TetraminisDetailsFactory
{
public:
	TetraminisDetailsFactory();
	~TetraminisDetailsFactory(void);

	static std::map<TetraminoDetailType, TetraminoDetailInformation> getDetailsTypesData();

private:

	static TetraminoDetailInformation getDetailType1Information();
	static TetraminoDetailInformation getDetailType2Information();
	static TetraminoDetailInformation getDetailType3Information();
	static TetraminoDetailInformation getDetailType4Information();
	static TetraminoDetailInformation getDetailType5Information();
	static TetraminoDetailInformation getDetailType6Information();
	static TetraminoDetailInformation getDetailType7Information();
	static TetraminoDetailInformation getDetailType8Information();

	static void copyMasiveToVectorInStructure(int *aSourceMassive, TetraminoDetailInformation &aInformation);
	static std::vector<int> getTetraminosElementsLineFromSource(int yIndex, int *aSourceMassive);

};

