#pragma once

#include "GameSystemInterface.h"
#include "ActiveDetails.h"

class MoveSystem :public GameSystemInterface
{
public:
	MoveSystem(ActiveDetails *aActiveDetailsStore);
	~MoveSystem(void);

	void updateSystem(float deltaTime);

private:

	ActiveDetails *_activeDetailsStore;

};

