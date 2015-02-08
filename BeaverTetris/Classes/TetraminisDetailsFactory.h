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

	static void copyMasiveToVectorInStructure(int *aSourceMassive, TetraminoDetailInformation &aInformation);
	static std::vector<int> getTetraminosElementsLineFromSource(int yIndex, int *aSourceMassive);

};

