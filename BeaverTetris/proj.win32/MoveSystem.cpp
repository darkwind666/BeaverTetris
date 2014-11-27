#include "MoveSystem.h"

using namespace std;

MoveSystem::MoveSystem(ActiveDetails *aActiveDetailsStore)
{
	_activeDetailsStore = aActiveDetailsStore;
}


MoveSystem::~MoveSystem(void)
{
}

void MoveSystem::updateSystem(float deltaTime)
{
	vector<TetraminoDetail*> tetraminoDetails = _activeDetailsStore->getActiveDetails();

	vector<TetraminoDetail*>::iterator tetraminoDetailsIterator;

	for (tetraminoDetailsIterator = tetraminoDetails.begin; tetraminoDetailsIterator != tetraminoDetails.end; tetraminoDetailsIterator++)
	{
		TetraminoDetail *tetraminoDetail = *tetraminoDetailsIterator;
		GamePositionOnBoard tetraminoDetailPosition = tetraminoDetail->getDetailPosition;
		tetraminoDetailPosition.yPosition = tetraminoDetailPosition.yPosition - 1;
	}

}
