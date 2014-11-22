#pragma once
class GameEventInterface
{
public:
	GameEventInterface(void);
	~GameEventInterface(void);

	virtual bool eventTime(void) = 0;
	virtual void runEvent(void) = 0;

};

