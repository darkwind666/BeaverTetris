#include "ActiveDetails.h"

using namespace std;

ActiveDetails::ActiveDetails(void)
{
	_tetraminoDetails = vector<TetraminoDetail*>();
}


ActiveDetails::~ActiveDetails(void)
{

}

void ActiveDetails::addDetail(TetraminoDetail *aDetail)
{
	_tetraminoDetails.push_back(aDetail);
}

void  ActiveDetails::removeDetail(TetraminoDetail *aDetail)
{
	vector<TetraminoDetail*>::iterator iteratorToNeedRemoveElement;
	iteratorToNeedRemoveElement = find(_tetraminoDetails.begin(), _tetraminoDetails.end(), aDetail);
	_tetraminoDetails.erase(iteratorToNeedRemoveElement);
}

vector<TetraminoDetail*> ActiveDetails::getActiveDetails()
{
	vector<TetraminoDetail*> tetraminoDetails = vector<TetraminoDetail*>(_tetraminoDetails);
	return tetraminoDetails;
}