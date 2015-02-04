#pragma once

#include <vector>
#include <functional>

class FullLineCombinationDelegate
{
public:
	FullLineCombinationDelegate(void);
	virtual ~FullLineCombinationDelegate(void);

	virtual void blowUpLine(int aLineIndex) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;
	virtual void setCallback(std::function<void()> aCallback) = 0;

};

