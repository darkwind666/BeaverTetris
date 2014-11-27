#pragma once

#include <vector>
#include "TetraminoDetail.h"

class ActiveDetails
{
public:
	ActiveDetails(void);
	~ActiveDetails(void);

	void addDetail(TetraminoDetail *aDetail);
	void removeDetail(TetraminoDetail *aDetail);
	std::vector<TetraminoDetail*> getActiveDetails();

private:

	std::vector<TetraminoDetail*> _tetraminoDetails;

};

