#pragma once

class AIStrategyInterface
{
public:
	AIStrategyInterface(void);
	~AIStrategyInterface(void);

	virtual void updateAI()=0;

};

